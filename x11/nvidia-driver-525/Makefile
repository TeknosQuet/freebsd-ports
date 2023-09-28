DISTVERSION=	525.125.06
# Explicitly set PORTREVISION as it can be overridden by the master port
PORTREVISION=	0

.if ${.CURDIR} == /usr/ports/x11/nvidia-driver-525
MASTERDIR=	${.CURDIR}/../nvidia-driver
.else
MASTERDIR=	/usr/ports/x11/nvidia-driver
.endif
PKGNAMESUFFIX=	-525

.include "${MASTERDIR}/Makefile"
