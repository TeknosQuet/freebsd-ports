--- server/ptrace.c.orig	2023-10-13 21:00:12 UTC
+++ server/ptrace.c
@@ -660,7 +660,7 @@ void set_thread_context( struct thread *thread, const 
     resume_after_ptrace( thread );
 }
 
-#elif defined(__i386__) && defined(PTRACE_GETDBREGS) && defined(PTRACE_SETDBREGS) && \
+#elif (defined(__i386__) || defined(__x86_64__)) && defined(PTRACE_GETDBREGS) && defined(PTRACE_SETDBREGS) && \
     (defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__))
 
 #include <machine/reg.h>
@@ -698,30 +698,79 @@ void get_thread_context( struct thread *thread, contex
     {
 #ifdef DBREG_DRX
         /* needed for FreeBSD, the structure fields have changed under 5.x */
-        context->debug.i386_regs.dr0 = DBREG_DRX((&dbregs), 0);
-        context->debug.i386_regs.dr1 = DBREG_DRX((&dbregs), 1);
-        context->debug.i386_regs.dr2 = DBREG_DRX((&dbregs), 2);
-        context->debug.i386_regs.dr3 = DBREG_DRX((&dbregs), 3);
-        context->debug.i386_regs.dr6 = DBREG_DRX((&dbregs), 6);
-        context->debug.i386_regs.dr7 = DBREG_DRX((&dbregs), 7);
+		switch (context->machine)
+		{
+		case IMAGE_FILE_MACHINE_I386:
+			context->debug.i386_regs.dr0 = DBREG_DRX((&dbregs), 0);
+			context->debug.i386_regs.dr1 = DBREG_DRX((&dbregs), 1);
+			context->debug.i386_regs.dr2 = DBREG_DRX((&dbregs), 2);
+			context->debug.i386_regs.dr3 = DBREG_DRX((&dbregs), 3);
+			context->debug.i386_regs.dr6 = DBREG_DRX((&dbregs), 6);
+			context->debug.i386_regs.dr7 = DBREG_DRX((&dbregs), 7);
+			break;
+		case IMAGE_FILE_MACHINE_AMD64:
+			context->debug.x86_64_regs.dr0 = DBREG_DRX((&dbregs), 0);
+			context->debug.x86_64_regs.dr1 = DBREG_DRX((&dbregs), 1);
+			context->debug.x86_64_regs.dr2 = DBREG_DRX((&dbregs), 2);
+			context->debug.x86_64_regs.dr3 = DBREG_DRX((&dbregs), 3);
+			context->debug.x86_64_regs.dr6 = DBREG_DRX((&dbregs), 6);
+			context->debug.x86_64_regs.dr7 = DBREG_DRX((&dbregs), 7);
+			break;
+		default:
+			set_error( STATUS_INVALID_PARAMETER );
+			goto done;
+		}
+		
 #elif defined(__NetBSD__)
-        context->debug.i386_regs.dr0 = dbregs.dr[0];
-        context->debug.i386_regs.dr1 = dbregs.dr[1];
-        context->debug.i386_regs.dr2 = dbregs.dr[2];
-        context->debug.i386_regs.dr3 = dbregs.dr[3];
-        context->debug.i386_regs.dr6 = dbregs.dr[6];
-        context->debug.i386_regs.dr7 = dbregs.dr[7];
+		switch (context->machine)
+		{
+		case IMAGE_FILE_MACHINE_I386:
+			context->debug.i386_regs.dr0 = dbregs.dr[0];
+			context->debug.i386_regs.dr1 = dbregs.dr[1];
+			context->debug.i386_regs.dr2 = dbregs.dr[2];
+			context->debug.i386_regs.dr3 = dbregs.dr[3];
+			context->debug.i386_regs.dr6 = dbregs.dr[6];
+			context->debug.i386_regs.dr7 = dbregs.dr[7];
+			break;
+		case IMAGE_FILE_MACHINE_AMD64:
+			context->debug.x86_64_regs.dr0 = dbregs.dr[0];
+			context->debug.x86_64_regs.dr1 = dbregs.dr[1];
+			context->debug.x86_64_regs.dr2 = dbregs.dr[2];
+			context->debug.x86_64_regs.dr3 = dbregs.dr[3];
+			context->debug.x86_64_regs.dr6 = dbregs.dr[6];
+			context->debug.x86_64_regs.dr7 = dbregs.dr[7];
+			break;
+		default:
+			set_error( STATUS_INVALID_PARAMETER );
+			goto done;
+		}
 #else
-        context->debug.i386_regs.dr0 = dbregs.dr0;
-        context->debug.i386_regs.dr1 = dbregs.dr1;
-        context->debug.i386_regs.dr2 = dbregs.dr2;
-        context->debug.i386_regs.dr3 = dbregs.dr3;
-        context->debug.i386_regs.dr6 = dbregs.dr6;
-        context->debug.i386_regs.dr7 = dbregs.dr7;
+		switch (context->machine)
+		{
+		case IMAGE_FILE_MACHINE_I386:
+			context->debug.i386_regs.dr0 = dbregs.dr0;
+			context->debug.i386_regs.dr1 = dbregs.dr1;
+			context->debug.i386_regs.dr2 = dbregs.dr2;
+			context->debug.i386_regs.dr3 = dbregs.dr3;
+			context->debug.i386_regs.dr6 = dbregs.dr6;
+			context->debug.i386_regs.dr7 = dbregs.dr7;
+			break;
+		case IMAGE_FILE_MACHINE_AMD64:
+			context->debug.x86_64_regs.dr0 = dbregs.dr0;
+			context->debug.x86_64_regs.dr1 = dbregs.dr1;
+			context->debug.x86_64_regs.dr2 = dbregs.dr2;
+			context->debug.x86_64_regs.dr3 = dbregs.dr3;
+			context->debug.x86_64_regs.dr6 = dbregs.dr6;
+			context->debug.x86_64_regs.dr7 = dbregs.dr7;
+			break;
+		default:
+			set_error( STATUS_INVALID_PARAMETER );
+			goto done;
+		}
 #endif
         context->flags |= SERVER_CTX_DEBUG_REGISTERS;
     }
-    resume_after_ptrace( thread );
+done: resume_after_ptrace( thread );
 }
 
 /* set the thread x86 registers */
@@ -737,32 +786,83 @@ void set_thread_context( struct thread *thread, const 
 
 #ifdef DBREG_DRX
     /* needed for FreeBSD, the structure fields have changed under 5.x */
-    DBREG_DRX((&dbregs), 0) = context->debug.i386_regs.dr0;
-    DBREG_DRX((&dbregs), 1) = context->debug.i386_regs.dr1;
-    DBREG_DRX((&dbregs), 2) = context->debug.i386_regs.dr2;
-    DBREG_DRX((&dbregs), 3) = context->debug.i386_regs.dr3;
-    DBREG_DRX((&dbregs), 4) = 0;
-    DBREG_DRX((&dbregs), 5) = 0;
-    DBREG_DRX((&dbregs), 6) = context->debug.i386_regs.dr6;
-    DBREG_DRX((&dbregs), 7) = context->debug.i386_regs.dr7;
+	switch (context->machine)
+	{
+	case IMAGE_FILE_MACHINE_I386:
+		DBREG_DRX((&dbregs), 0) = context->debug.i386_regs.dr0;
+		DBREG_DRX((&dbregs), 1) = context->debug.i386_regs.dr1;
+		DBREG_DRX((&dbregs), 2) = context->debug.i386_regs.dr2;
+		DBREG_DRX((&dbregs), 3) = context->debug.i386_regs.dr3;
+		DBREG_DRX((&dbregs), 4) = 0;
+		DBREG_DRX((&dbregs), 5) = 0;
+		DBREG_DRX((&dbregs), 6) = context->debug.i386_regs.dr6;
+		DBREG_DRX((&dbregs), 7) = context->debug.i386_regs.dr7;
+		break;
+	case IMAGE_FILE_MACHINE_AMD64:
+		DBREG_DRX((&dbregs), 0) = context->debug.x86_64_regs.dr0;
+		DBREG_DRX((&dbregs), 1) = context->debug.x86_64_regs.dr1;
+		DBREG_DRX((&dbregs), 2) = context->debug.x86_64_regs.dr2;
+		DBREG_DRX((&dbregs), 3) = context->debug.x86_64_regs.dr3;
+		DBREG_DRX((&dbregs), 4) = 0;
+		DBREG_DRX((&dbregs), 5) = 0;
+		DBREG_DRX((&dbregs), 6) = context->debug.x86_64_regs.dr6;
+		DBREG_DRX((&dbregs), 7) = context->debug.x86_64_regs.dr7;
+		break;
+	default:
+		set_error( STATUS_INVALID_PARAMETER );
+	}
 #elif defined(__NetBSD__)
-    dbregs.dr[0] = context->debug.i386_regs.dr0;
-    dbregs.dr[1] = context->debug.i386_regs.dr1;
-    dbregs.dr[2] = context->debug.i386_regs.dr2;
-    dbregs.dr[3] = context->debug.i386_regs.dr3;
-    dbregs.dr[4] = 0;
-    dbregs.dr[5] = 0;
-    dbregs.dr[6] = context->debug.i386_regs.dr6;
-    dbregs.dr[7] = context->debug.i386_regs.dr7;
+	switch (context->machine)
+	{
+	case IMAGE_FILE_MACHINE_I386:
+    	dbregs.dr[0] = context->debug.i386_regs.dr0;
+    	dbregs.dr[1] = context->debug.i386_regs.dr1;
+    	dbregs.dr[2] = context->debug.i386_regs.dr2;
+    	dbregs.dr[3] = context->debug.i386_regs.dr3;
+    	dbregs.dr[4] = 0;
+    	dbregs.dr[5] = 0;
+    	dbregs.dr[6] = context->debug.i386_regs.dr6;
+    	dbregs.dr[7] = context->debug.i386_regs.dr7;
+		break;
+	case IMAGE_FILE_MACHINE_AMD64:
+    	dbregs.dr[0] = context->debug.x86_64_regs.dr0;
+    	dbregs.dr[1] = context->debug.x86_64_regs.dr1;
+    	dbregs.dr[2] = context->debug.x86_64_regs.dr2;
+    	dbregs.dr[3] = context->debug.x86_64_regs.dr3;
+    	dbregs.dr[4] = 0;
+    	dbregs.dr[5] = 0;
+    	dbregs.dr[6] = context->debug.x86_64_regs.dr6;
+    	dbregs.dr[7] = context->debug.x86_64_regs.dr7;
+		break;
+	default:
+		set_error( STATUS_INVALID_PARAMETER );
+	}
 #else
-    dbregs.dr0 = context->debug.i386_regs.dr0;
-    dbregs.dr1 = context->debug.i386_regs.dr1;
-    dbregs.dr2 = context->debug.i386_regs.dr2;
-    dbregs.dr3 = context->debug.i386_regs.dr3;
-    dbregs.dr4 = 0;
-    dbregs.dr5 = 0;
-    dbregs.dr6 = context->debug.i386_regs.dr6;
-    dbregs.dr7 = context->debug.i386_regs.dr7;
+	switch (context->machine)
+	{
+	case IMAGE_FILE_MACHINE_I386:
+		dbregs.dr0 = context->debug.i386_regs.dr0;
+		dbregs.dr1 = context->debug.i386_regs.dr1;
+		dbregs.dr2 = context->debug.i386_regs.dr2;
+		dbregs.dr3 = context->debug.i386_regs.dr3;
+		dbregs.dr4 = 0;
+		dbregs.dr5 = 0;
+		dbregs.dr6 = context->debug.i386_regs.dr6;
+		dbregs.dr7 = context->debug.i386_regs.dr7;
+		break;
+	case IMAGE_FILE_MACHINE_AMD64:
+		dbregs.dr0 = context->debug.x86_64_regs.dr0;
+		dbregs.dr1 = context->debug.x86_64_regs.dr1;
+		dbregs.dr2 = context->debug.x86_64_regs.dr2;
+		dbregs.dr3 = context->debug.x86_64_regs.dr3;
+		dbregs.dr4 = 0;
+		dbregs.dr5 = 0;
+		dbregs.dr6 = context->debug.x86_64_regs.dr6;
+		dbregs.dr7 = context->debug.x86_64_regs.dr7;
+		break;
+	default:
+		set_error( STATUS_INVALID_PARAMETER );
+	}
 #endif
     if (ptrace( PTRACE_SETDBREGS, pid, (caddr_t)&dbregs, 0 ) != -1)
     {
