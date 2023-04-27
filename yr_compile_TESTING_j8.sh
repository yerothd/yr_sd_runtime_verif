#!/bin/bash
#AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
#EMAIL: yeroth.d@gmail.com

YR_ERRORS_LOG_FILE="yr_errors.log"

clear && qmake yr_sd_runtime_verif_TESTING.pro && make clean 

OUT_CMD_TIME=$(time make -j8 > /dev/null 2> "${YR_ERRORS_LOG_FILE}")

val=$(cat "${YR_ERRORS_LOG_FILE}" | grep 'error\|ERROR\|Error' | wc -l)

if [ ${val} -eq 0 ]; then
	rm -f "${YR_ERRORS_LOG_FILE}" 
	echo "[compilation avec succes]"
else
	echo "[compilation avec des erreurs (${val})]"
fi

echo ${OUT_CMD_TIME}


