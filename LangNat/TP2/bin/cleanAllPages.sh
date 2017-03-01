FOLDER=$1
BLIKI="/home/ceramisch/Work/tools/corpus-proc/bliki"
CLASSPATH="${BLIKI}/bliki-core/target/bliki-core-3.1.01-SNAPSHOT.jar:.:/usr/share/java/slf4j-api.jar:/usr/share/java/slf4j-nop.jar:${BLIKI}/commons-lang3-3.1.jar"

javac -cp $CLASSPATH CleanPages.java
mkdir -p $FOLDER/clean
rm -rf $FOLDER/clean/*

for file in $(ls $FOLDER/); do
    java -cp $CLASSPATH CleanPages $FOLDER/$file > $FOLDER/clean/$file
done

# All intermediary files can be gzipped to save space
#tar cfz $FOLDER/wiki.tar.gz $FOLDER/wiki
#rm -r $FOLDER/wiki

# Remove compiled java class, to avoid version problems
# rm CleanPages.class
