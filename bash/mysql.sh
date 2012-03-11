#!/bin/bash
#
declare -a TABLES
TABLES=($(mysql --user=admin1 --password=s3cr3tpass45 --database=python -e "show tables"))
# Need one less
echo "Total tables: "$((${#TABLES[@]}-1))


