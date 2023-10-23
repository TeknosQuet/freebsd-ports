--- dlls/ntdll/unix/thread.c.orig	2023-10-13 21:00:12 UTC
+++ dlls/ntdll/unix/thread.c
@@ -1910,7 +1910,7 @@ static void set_native_thread_name( HANDLE handle, con
         write( fd, nameA, len );
         close( fd );
     }
-#elif defined(__APPLE__)
+#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
     /* pthread_setname_np() silently fails if the name is longer than 63 characters + null terminator */
     char nameA[64];
     NTSTATUS status;
@@ -1931,8 +1931,12 @@ static void set_native_thread_name( HANDLE handle, con
     if (status != STATUS_SUCCESS || unix_pid == -1 || unix_tid == -1)
         return;
 
+#if defined(__APPLE__)
     current_tid = mach_thread_self();
     mach_port_deallocate(mach_task_self(), current_tid);
+#else // FreeBSD
+	current_tid = pthread_self();
+#endif
 
     if (unix_tid != current_tid)
     {
@@ -1943,7 +1947,12 @@ static void set_native_thread_name( HANDLE handle, con
 
     len = ntdll_wcstoumbs( name->Buffer, name->Length / sizeof(WCHAR), nameA, sizeof(nameA) - 1, FALSE );
     nameA[len] = '\0';
+#if defined(__APPLE__)
     pthread_setname_np(nameA);
+#else // FreeBSD
+	pthread_setname_np(current_tid, nameA);
+#endif
+
 #else
     static int once;
     if (!once++) FIXME("not implemented on this platform\n");
