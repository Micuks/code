if diff data.out std.out ; then
    printf "AC\n"
else 
    printf "WA\n"
    exit 0;
fi