mkdir -p pdfs/
rm -f pdfs/*.pdf
root -b -q doAll.C
gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=merged.pdf pdfs/*.pdf
filename=mergedTEST.pdf
cp merged.pdf ~/public_html/dump/$filename
# scp merged.pdf squark.physics.ucsb.edu:~/Desktop/$filename
