PORTNAME=		ghidra
DISTVERSION=	11.0.3
CATEGORIES=		devel java security
MASTER_SITES=	https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/android4me/:axmlprinter2 \
				https://sourceforge.net/projects/pydev/files/pydev/PyDev%206.3.1/:pydev \
				https://archive.eclipse.org/tools/cdt/releases/8.6/:cdt \
				https://github.com/pxb1988/dex2jar/releases/download/v2.1/:dex2jar \
				https://github.com/NationalSecurityAgency/ghidra-data/raw/Ghidra_${DISTVERSION}/lib/:sarif \
				https://sourceforge.net/projects/yajsw/files/yajsw/yajsw-stable-13.09/:yajsw
PKGNAMESUFFIX=	11
DISTFILES=		AXMLPrinter2.jar:axmlprinter2 \
				PyDev%206.3.1.zip:pydev \
				cdt-8.6.0.zip:cdt \
				dex2jar-2.1.zip:dex2jar \
				java-sarif-2.1-modified.jar:sarif \
				yajsw-stable-13.09.zip:yajsw
DIST_SUBDIR=	${PORTNAME}

MAINTAINER=	teknosquet@danwin1210.de
COMMENT=	SRE framework developed by the NSA
WWW=		https://ghidra-sre.org

LICENSE=		APACHE20
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 arm64

EXTRACT_DEPENDS=	${UNZIP_CMD}:archivers/unzip
BUILD_DEPENDS=		flex:textproc/flex \
					fop:textproc/fop \
					gradle>=7.3:devel/gradle \
					protobuf>=3.21.8:devel/protobuf

USES=		bison cpe shebangfix
USE_GCC=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	NationalSecurityAgency
GH_PROJECT=	ghidra
GH_TAGNAME=	Ghidra_${DISTVERSION}_build

USE_JAVA=		yes
JAVA_VERSION=	17+
JAVA_BUILD=		yes
JAVA_RUN=		yes

# Not sure why, but I have to define JAVA_HOME within this command or it will
# default to what JAVA_HOME already is.
# Run Gradle w/o daemon and display failures.
MAKE_ENV=	JAVA_HOME=${JAVA_HOME}
GRADLE_RUN=	${SETENV} ${MAKE_ENV} gradle \
			--build-cache \
			--no-daemon \
			--offline \
			--parallel

CPE_VENDOR=	nsa

DEPEND_DIR=	${WRKDIR}/ghidra-Ghidra_${DISTVERSION}_build/dependencies

post-extract:
	${MKDIR} ${DEPEND_DIR}/flatRepo ${DEPEND_DIR}/GhidraDev ${DEPEND_DIR}/GhidraServer
	${CP} ${DISTDIR}/${DIST_SUBDIR}/AXMLPrinter2.jar ${DISTDIR}/${DIST_SUBDIR}/java-sarif-2.1-modified.jar ${DEPEND_DIR}/flatRepo
	${UNZIP_CMD} -j -d ${DEPEND_DIR}/flatRepo ${DISTDIR}/${DIST_SUBDIR}/dex2jar-2.1.zip
	${CP} ${DISTDIR}/${DIST_SUBDIR}/PyDev%206.3.1.zip ${DISTDIR}/${DIST_SUBDIR}/cdt-8.6.0.zip ${DEPEND_DIR}/GhidraDev
	${CP} ${DISTDIR}/${DIST_SUBDIR}/yajsw-stable-13.09.zip ${DEPEND_DIR}/GhidraServer

do-build:
	cd ${WRKSRC} && \
	${GRADLE_RUN} buildGhidra

do-install:
	${UNZIP_CMD} -d ${STAGEDIR} ${WRKSRC}/build/dist/*.zip
	${MV} ${STAGEDIR}/ghidra* ${STAGEDIR}${DATADIR}
	${CP} ${WRKDIR}/ghidra-Ghidra_${DISTVERSION}_build/Ghidra/RuntimeScripts/Linux/ghidraRun ${STAGEDIR}${PREFIX}/bin/ghidra
	${CP} ${WRKDIR}/ghidra-Ghidra_${DISTVERSION}_build/Ghidra/RuntimeScripts/Linux/server/ghidraSvr ${STAGEDIR}${PREFIX}/bin/ghidra-server
	${CP} ${WRKDIR}/ghidra-Ghidra_${DISTVERSION}_build/Ghidra/RuntimeScripts/Linux/support/launch.sh ${STAGEDIR}${PREFIX}/share/ghidra/support/launch.sh

.include <bsd.port.mk>
