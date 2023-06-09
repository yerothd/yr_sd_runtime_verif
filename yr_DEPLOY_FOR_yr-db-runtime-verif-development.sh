

YR_DB_RUNTIME_VERIF_HOME_DEVEL="${HOME}/yr-db-runtime-verif"

YR_DB_RUNTIME_VERIF_HOME_DEVEL_SRC="${YR_DB_RUNTIME_VERIF_HOME_DEVEL}/src"

YR_SD_RUNTIME_VERIF="yr_sd_runtime_verif"

SRC="src"

cp "${SRC}"/*.hpp "${YR_DB_RUNTIME_VERIF_HOME_DEVEL_SRC}/${YR_SD_RUNTIME_VERIF}"

cp "${SRC}"/utils/YR_CPP_UTILS.hpp \
	"${YR_DB_RUNTIME_VERIF_HOME_DEVEL_SRC}/${YR_SD_RUNTIME_VERIF}/utils" 

cp "${SRC}"/yr-expressions-conditions/*.HPP \
	"${YR_DB_RUNTIME_VERIF_HOME_DEVEL_SRC}/${YR_SD_RUNTIME_VERIF}/yr-expressions-conditions"

mkdir -p "${YR_DB_RUNTIME_VERIF_HOME_DEVEL}/lib_SD"

cp lib/"lib${YR_SD_RUNTIME_VERIF}".a "${YR_DB_RUNTIME_VERIF_HOME_DEVEL}/lib_SD"
