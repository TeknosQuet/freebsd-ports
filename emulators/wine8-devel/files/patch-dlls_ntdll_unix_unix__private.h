--- dlls/ntdll/unix/unix_private.h.orig	2023-10-13 01:36:10 UTC
+++ dlls/ntdll/unix/unix_private.h
@@ -175,7 +175,6 @@ extern void init_startup_info(void) DECLSPEC_HIDDEN;
 extern void *create_startup_info( const UNICODE_STRING *nt_image, const RTL_USER_PROCESS_PARAMETERS *params,
                                   const pe_image_info_t *pe_info, DWORD *info_size ) DECLSPEC_HIDDEN;
 extern char **build_envp( const WCHAR *envW ) DECLSPEC_HIDDEN;
-extern char *get_alternate_wineloader( WORD machine ) DECLSPEC_HIDDEN;
 extern NTSTATUS exec_wineloader( char **argv, int socketfd, const pe_image_info_t *pe_info ) DECLSPEC_HIDDEN;
 extern NTSTATUS load_builtin( const pe_image_info_t *image_info, WCHAR *filename, USHORT machine,
                               void **addr_ptr, SIZE_T *size_ptr, ULONG_PTR limit_low, ULONG_PTR limit_high ) DECLSPEC_HIDDEN;
