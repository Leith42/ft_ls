# ft_ls
My own implementation of the most used Unix command `ls` with some of its options. ACL and extended attributes are managed.

## Using it
```
usage: ft_ls [-lrRatSUu] [file ...]
```
ft_ls can be used exactly as the original command with the following options :

|Option|Action
|-|-|
|`-l`|   use a long listing format
|`-R`|   list subdirectories recursively
|`-a`|   do not hide entries starting with .
|`-r`|   reverse order while sorting
|`-t`|   sort by modification time
|`-S`|   sort by file size, largest first
|`-U`|   sort by creation time
|`-u`|   sort by access time
