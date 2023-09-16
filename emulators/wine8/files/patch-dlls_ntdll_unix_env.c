--- dlls/ntdll/unix/env.c.orig	2023-09-16 02:43:50 UTC
+++ dlls/ntdll/unix/env.c
@@ -354,7 +354,6 @@ static BOOL is_dynamic_env_var( const char *var )
             STARTS_WITH( var, "WINEHOMEDIR=" ) ||
             STARTS_WITH( var, "WINEBUILDDIR=" ) ||
             STARTS_WITH( var, "WINECONFIGDIR=" ) ||
-            STARTS_WITH( var, "WINELOADER=" ) ||
             STARTS_WITH( var, "WINEDLLDIR" ) ||
             STARTS_WITH( var, "WINEUNIXCP=" ) ||
             STARTS_WITH( var, "WINEUSERLOCALE=" ) ||
@@ -1085,7 +1084,6 @@ static void add_dynamic_environment( WCHAR **env, SIZE
     sprintf( str, "WINEDLLDIR%u", i );
     append_envW( env, pos, size, str, NULL );
     add_system_dll_path_var( env, pos, size );
-    append_envA( env, pos, size, "WINELOADER", wineloader );
     append_envA( env, pos, size, "WINEUSERNAME", user_name );
     append_envA( env, pos, size, "WINEDLLOVERRIDES", overrides );
     if (unix_cp.CodePage != CP_UTF8)
@@ -1863,7 +1861,7 @@ static void init_peb( RTL_USER_PROCESS_PARAMETERS *par
         NtCurrentTeb()->Tib.ExceptionList = (void *)((char *)NtCurrentTeb() + teb_offset);
         wow_peb = (PEB32 *)((char *)peb + page_size);
         set_thread_id( NtCurrentTeb(),  GetCurrentProcessId(), GetCurrentThreadId() );
-        ERR( "starting %s in experimental wow64 mode\n", debugstr_us(&params->ImagePathName) );
+        WARN( "starting %s in experimental wow64 mode\n", debugstr_us(&params->ImagePathName) );
     }
 #endif
 
