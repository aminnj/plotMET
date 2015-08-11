filename=merged.pdf
if [ $# -gt 0 ]; then
    filename=$1
fi
echo "output will be $filename"

mkdir -p pdfs/
rm -f pdfs/*.pdf
root -b -q doAll.C
gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$filename pdfs/*.pdf
cp $filename ~/public_html/dump/$filename
echo ">>> uaf-6.t2.ucsd.edu/~namin/dump/$filename"
# scp merged.pdf squark.physics.ucsb.edu:~/Desktop/$filename
scp -rp pdfs/ squark.physics.ucsb.edu:~/Desktop/pdfs/
