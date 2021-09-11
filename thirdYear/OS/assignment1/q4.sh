countFiles(){
    local count=0
    # echo arg:$1 >&2
    for fldir in $(ls $1)
    do
        local fldr="$1/$fldir"
        # echo lsopt:$fldr >&2
        if [ -d $fldr ];
        then
            local c=$(countFiles $fldr)
            # echo c:$c >&2
            ((count+=c))
        else
            ((count+=1))
        fi
    done
    echo $count
}

echo $(pwd)
fcount=$(countFiles $(pwd))

echo $fcount
