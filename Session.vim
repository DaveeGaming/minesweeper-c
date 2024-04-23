let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd D:/Stuff/Coding/c/raylibtest
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +1 D:/Stuff/Coding/c/raylibtest
badd +19 main.c
badd +1 global.c
badd +3 global.h
badd +18 CMakeLists.txt
badd +52 game.c
badd +7 game.h
badd +51 build/_deps/raylib-src/src/raymath.h
argglobal
%argdel
$argadd D:/Stuff/Coding/c/raylibtest
edit game.c
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 77 + 78) / 156)
exe '2resize ' . ((&lines * 21 + 22) / 44)
exe 'vert 2resize ' . ((&columns * 78 + 78) / 156)
exe '3resize ' . ((&lines * 20 + 22) / 44)
exe 'vert 3resize ' . ((&columns * 78 + 78) / 156)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 37 - ((27 * winheight(0) + 21) / 42)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 37
normal! 046|
lcd D:/Stuff/Coding/c/raylibtest
wincmd w
argglobal
if bufexists(fnamemodify("D:/Stuff/Coding/c/raylibtest/CMakeLists.txt", ":p")) | buffer D:/Stuff/Coding/c/raylibtest/CMakeLists.txt | else | edit D:/Stuff/Coding/c/raylibtest/CMakeLists.txt | endif
if &buftype ==# 'terminal'
  silent file D:/Stuff/Coding/c/raylibtest/CMakeLists.txt
endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 18 - ((16 * winheight(0) + 10) / 21)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 18
normal! 069|
lcd D:/Stuff/Coding/c/raylibtest
wincmd w
argglobal
if bufexists(fnamemodify("D:/Stuff/Coding/c/raylibtest/main.c", ":p")) | buffer D:/Stuff/Coding/c/raylibtest/main.c | else | edit D:/Stuff/Coding/c/raylibtest/main.c | endif
if &buftype ==# 'terminal'
  silent file D:/Stuff/Coding/c/raylibtest/main.c
endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 19 - ((14 * winheight(0) + 10) / 20)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 19
normal! 014|
lcd D:/Stuff/Coding/c/raylibtest
wincmd w
exe 'vert 1resize ' . ((&columns * 77 + 78) / 156)
exe '2resize ' . ((&lines * 21 + 22) / 44)
exe 'vert 2resize ' . ((&columns * 78 + 78) / 156)
exe '3resize ' . ((&lines * 20 + 22) / 44)
exe 'vert 3resize ' . ((&columns * 78 + 78) / 156)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
