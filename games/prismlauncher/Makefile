PORTNAME=	prismlauncher
DISTVERSION=	8.3
CATEGORIES=	games java

MAINTAINER=	teknosquet@danwin1210.de
COMMENT=	Minecraft launcher with the ability to manage multiple instances
WWW=		https://prismlauncher.org

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/COPYING.md

LIB_DEPENDS=	libcmark.so:textproc/cmark \
		libtomlplusplus.so:devel/tomlplusplus \
		libquazip1-qt6.so:archivers/quazip

USES=	cmake compiler:c++17-lang kde:5 qt:6

USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	PrismLauncher
GH_PROJECT=	PrismLauncher
GH_TUPLE=	gulrak:filesystem:2fc4b46:filesystem/libraries/filesystem \
		PrismLauncher:libnbtplusplus:23b9551:libnbtplusplus/libraries/libnbtplusplus

USE_JAVA=	yes
JAVA_VERSION=	8 11 17 18 19
JAVA_BUILD=	JDK
JAVA_RUN=	yes

USE_KDE=	ecm:build

USE_QT=	5compat base

CMAKE_ARGS+=	-DCMAKE_BUILD_TYPE=Release \
		-DENABLE_LTO=ON \
		-DJAVA_HOME=${JAVA_HOME} \
		-DJava_JAVAC_EXECUTABLE=${JAVAC} \
		-DLauncher_BUILD_PLATFORM="freebsd" \
		-DLauncher_QT_VERSION_MAJOR="6"

.include <bsd.port.mk>
