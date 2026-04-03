int Search_Seq1(SSTable ST, KeyType key) {
    for(int i = 1; i <= ST.length; i++)
        if(ST.elem[i] == key)
            return i;
    return 0;
}
