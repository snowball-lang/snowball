[2K[1;32m      Compiling[0m [>                                                                     ] 0 %[2K[1;32m      Compiling[0m [=====================>                                                ] 30 %[2K[1;32m      Compiling[0m [===================================>                                  ] 50 %[2K[1;32m      Compiling[0m [======================================>                               ] 55 %

[0;90m      ╭─[[0m[1;34mtests/main.sn[1;30m:30:7[0m[0;90m][0m
[0;90m      │[0m
[0;90m      │[0m
   [1;30m29[0;90m │ [1;37m
 [1;30m> 30[0;90m │ [1;37m    c = new Child()
      [0;90m│[0m [1;31m      ~ This is the call causing the error.[0m
   [1;30m31[0;90m │ [1;37m
[0;90m      │
[1;36m  note[1;30m:[0m Errored trying to call function `operator =`!
[1;30m      │  [0m With type `function (Child*, Child, ) -> Child`
[0;90m      │
[0;90m      │
[0;90m      :
[0;90m      │
[0;90m      ├─[[0m[1;34mtests/main.sn[1;30m:30:13[0m[0;90m][0m
[0;90m      │[0m
[0;90m      │[0m
   [1;30m29[0;90m │ [1;37m
 [1;30m> 30[0;90m │ [1;37m    c = new Child()
      [0;90m│[0m [1;31m            ~~~~~ this is the value that's causing the error[0m
   [1;30m31[0;90m │ [1;37m
[0;90m      │
[1;32m  help[1;30m:[0m Maybe try to convert a cast to the correct type?
[0;90m      │
[0;90m      │
   ───╯[0m

[1;31merror[0m: ([1;31mType Error[0m) [1mCan't assign value with type 'Child*' to a parameter with type 'Child'![0m


