while true ; do
./random < RANDOM > data.in
./t6 < data.in > my.out
./t6_std < data.in > std.out
    if diff my.out std.out ; then
        printf "AC\n"
    else 
        printf "WA\n"
        exit 0;
    fi
done