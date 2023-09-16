--- dlls/ntdll/unix/loader.c.orig	2023-09-16 02:46:25 UTC
+++ dlls/ntdll/unix/loader.c
@@ -378,10 +378,10 @@ static const BOOL use_preloader = TRUE;
 static const BOOL use_preloader = FALSE;
 #endif
 
+static char *argv0;
 static const char *bin_dir;
 static const char *dll_dir;
 static const char *ntdll_dir;
-static const char *wineloader;
 static SIZE_T dll_path_maxlen;
 static int *p___wine_main_argc;
 static char ***p___wine_main_argv;
@@ -618,10 +618,8 @@ static void set_config_dir(void)
 static void init_paths( char *argv[] )
 {
     Dl_info info;
-    char *basename, *env;
 
-    if ((basename = strrchr( argv[0], '/' ))) basename++;
-    else basename = argv[0];
+    argv0 = strdup( argv[0] );
 
     if (!dladdr( init_paths, &info ) || !(ntdll_dir = realpath_dirname( info.dli_fname )))
         fatal_error( "cannot get path to ntdll.so\n" );
@@ -640,18 +638,13 @@ static void init_paths( char *argv[] )
                 bin_dir = realpath_dirname( path );
             free( path );
         }
+#else
+	bin_dir = realpath_dirname( argv0 );
 #endif
         if (!bin_dir) bin_dir = build_path( dll_dir, DLL_TO_BINDIR );
         data_dir = build_path( bin_dir, BIN_TO_DATADIR );
-        wineloader = build_path( bin_dir, basename );
     }
-    else wineloader = build_path( build_path( build_dir, "loader" ), basename );
 
-    env = malloc( sizeof("WINELOADER=") + strlen(wineloader) );
-    strcpy( env, "WINELOADER=" );
-    strcat( env, wineloader );
-    putenv( env );
-
     set_dll_path();
     set_system_dll_path();
     set_home_dir();
@@ -689,27 +682,35 @@ static void preloader_exec( char **argv )
     execv( argv[1], argv + 1 );
 }
 
-/* exec the appropriate wine loader for the specified machine */
-static NTSTATUS loader_exec( char **argv, WORD machine )
+static NTSTATUS loader_exec( const char *loader, char **argv, WORD machine )
 {
-    if (machine != current_machine)
+    char *p, *path;    
+
+    if (build_dir)
     {
-        if (machine == IMAGE_FILE_MACHINE_AMD64)  /* try the 64-bit loader */
-        {
-            size_t len = strlen(wineloader);
+        argv[1] = build_path( build_dir, (machine == IMAGE_FILE_MACHINE_AMD64) ? "loader/wine64" : "loader/wine" );
+	preloader_exec( argv );
+	return STATUS_INVALID_IMAGE_FORMAT;
+    }
 
-            if (len <= 2 || strcmp( wineloader + len - 2, "64" ))
-            {
-                argv[1] = malloc( len + 3 );
-                strcpy( argv[1], wineloader );
-                strcat( argv[1], "64" );
-                preloader_exec( argv );
-            }
-        }
-        else if ((argv[1] = remove_tail( wineloader, "64" ))) preloader_exec( argv );
+    if ((p = strrchr( loader, '/' ))) loader = p + 1;
+
+    argv[1] = build_path( bin_dir, loader );
+    preloader_exec( argv );
+
+    argv[1] = getenv( "WINELOADER" );
+    if (argv[1]) preloader_exec( argv );
+
+    if ((path = getenv( "PATH" )))
+    {
+        for (p = strtok( strdup( path ), ":" ); p; p = strtok( NULL, ":" ))
+	{
+            argv[1] = build_path (p, loader );
+	    preloader_exec( argv );
+	}
     }
 
-    argv[1] = strdup( wineloader );
+    argv[1] = build_path( BINDIR, loader );
     preloader_exec( argv );
     return STATUS_INVALID_IMAGE_FORMAT;
 }
@@ -725,11 +726,41 @@ NTSTATUS exec_wineloader( char **argv, int socketfd, c
     WORD machine = pe_info->machine;
     ULONGLONG res_start = pe_info->base;
     ULONGLONG res_end = pe_info->base + pe_info->map_size;
+    const char *loader = argv0;
+    const char *loader_env = getenv( "WINELOADER" );
     char preloader_reserve[64], socket_env[64];
+    BOOL is_child_64bit;
 
     if (pe_info->image_flags & IMAGE_FLAGS_WineFakeDll) res_start = res_end = 0;
     if (pe_info->image_flags & IMAGE_FLAGS_ComPlusNativeReady) machine = native_machine;
 
+    is_child_64bit = is_machine_64bit( machine );
+
+    if (!is_win64 ^ !is_child_64bit)
+    {
+        if (loader_env)
+        {
+            int len = strlen( loader_env );
+	    char *env = malloc( sizeof("WINELOADER=") + len + 2 );
+
+	    if (!env) return STATUS_NO_MEMORY;
+	    strcpy( env, "WINELOADER=" );
+	    strcat( env, loader_env );
+	    if (is_child_64bit)
+            {
+                strcat( env, "64" );
+            }
+	    else
+            {
+                len += sizeof("WINELOADER=") - 1;
+		if (!strcmp( env + len - 2, "64" )) env[len-2] = 0;
+	    }
+	    loader = env;
+	    putenv( env );
+	}
+	else loader = is_child_64bit ? "wine64" : "wine";
+    }
+
     signal( SIGPIPE, SIG_DFL );
 
     sprintf( socket_env, "WINESERVERSOCKET=%u", socketfd );
@@ -739,7 +770,7 @@ NTSTATUS exec_wineloader( char **argv, int socketfd, c
     putenv( preloader_reserve );
     putenv( socket_env );
 
-    return loader_exec( argv, machine );
+    return loader_exec( loader, argv, machine );
 }
 
 
@@ -2410,7 +2441,7 @@ void __wine_main( int argc, char *argv[], char *envp[]
 
             memcpy( new_argv + 1, argv, (argc + 1) * sizeof(*argv) );
             putenv( noexec );
-            loader_exec( new_argv, current_machine );
+            loader_exec( argv0, new_argv, current_machine );
             fatal_error( "could not exec the wine loader\n" );
         }
     }
