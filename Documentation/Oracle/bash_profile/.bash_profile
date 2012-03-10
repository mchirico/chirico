# .bash_profile

# Get the aliases and functions
if [ -f ~/.bashrc ]; then
	. ~/.bashrc
fi

# User specific environment and startup programs

ORACLE_BASE=/u01/app/oracle
ORACLE_SID=orcl
export ORACLE_BASE ORACLE_SID



PATH=$PATH:$HOME/bin:/u01/app/oracle/product/11.1.0/db_1/bin

export PATH
