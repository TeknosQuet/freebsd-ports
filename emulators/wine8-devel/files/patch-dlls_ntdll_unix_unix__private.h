--- dlls/ntdll/unix/unix_private.h.orig	2023-11-24 21:48:09 UTC
+++ dlls/ntdll/unix/unix_private.h
@@ -181,7 +181,6 @@ extern char **build_envp( const WCHAR *envW );
 extern void *create_startup_info( const UNICODE_STRING *nt_image, const RTL_USER_PROCESS_PARAMETERS *params,
                                   const pe_image_info_t *pe_info, DWORD *info_size );
 extern char **build_envp( const WCHAR *envW );
-extern char *get_alternate_wineloader( WORD machine );
 extern NTSTATUS exec_wineloader( char **argv, int socketfd, const pe_image_info_t *pe_info );
 extern NTSTATUS load_builtin( const pe_image_info_t *image_info, WCHAR *filename, USHORT machine,
                               void **addr_ptr, SIZE_T *size_ptr, ULONG_PTR limit_low, ULONG_PTR limit_high );
