inf=$1
tmpt=`date +"%s.%N"`
tmpf=/tmp/${tmpt}
sed -e 's/^#line/\/\/#line/' ${inf} > ${tmpf}
mv ${tmpf} ${inf}
