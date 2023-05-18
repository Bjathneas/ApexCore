echo "echo Restoring environment" > "/home/gameforabit/Documents/ApexCore/build/debug/conan/deactivate_conanrunenv-debug-x86_64.sh"
for v in 
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "/home/gameforabit/Documents/ApexCore/build/debug/conan/deactivate_conanrunenv-debug-x86_64.sh"
    else
        echo unset $v >> "/home/gameforabit/Documents/ApexCore/build/debug/conan/deactivate_conanrunenv-debug-x86_64.sh"
    fi
done

