CATEGORY=$1
LANG=fr

mkdir -p $CATEGORY

cat $CATEGORY-url.txt |
awk 'BEGIN{ FS="\t"; getline;}{print "http://" lang ".wikipedia.org/wiki/" $2 "?action=raw&templates=expand" }' lang=$LANG |
wget --restrict-file-names=ascii -i - -P $CATEGORY/
