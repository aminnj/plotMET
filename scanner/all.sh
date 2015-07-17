rm -f pdfs/*.pdf
root -b -q doAll.C
gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=merged.pdf pdfs/*.pdf
# cp merged.pdf ~/public_html/dump/merged2.pdf
# cp merged.pdf ~/public_html/dump/merged.pdf
scp merged.pdf squark.physics.ucsb.edu:~/Desktop/mergedMET.pdf
# scp -rp pdfs squark.physics.ucsb.edu:~/Desktop/pdfs_met
