rm -f pdfs/*.pdf
root -b -q doAll.C
gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=mergedCMS3.pdf pdfs/*.pdf
cp mergedCMS3.pdf ~/public_html/dump/
# scp mergedCMS3.pdf squark.physics.ucsb.edu:~/Desktop/
