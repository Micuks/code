set nocompatible              " required
set noshowmode
filetype off                  " required

" set the runtime path to include vim-plug and initialize
let data_dir = has('nvim') ? stdpath('data') . '/site' : '~/.vim'
if empty(glob(data_dir . '/autoload/plug.vim'))
  silent execute '!curl -fLo '.data_dir.'/autoload/plug.vim --create-dirs  https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim'
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

call plug#begin()
"Display function signatures from completions in the command line
Plug 'Shougo/echodoc.vim'

"LeaderF
Plug 'Yggdroot/LeaderF', { 'do': ':LeaderfInstallCExtension' }

"Enhanced highlight
Plug 'octol/vim-cpp-enhanced-highlight'

"Enhanced keybinds
Plug 'tpope/vim-unimpaired'

"New objects
"di 或 ci, 一次性删除/改写当前参数
"ii 和 ai ：缩进对象，同一个缩进层次的代码，可以用 vii 选中，dii / cii 删除或改写
"if 和 af ：函数对象，可以用 vif / dif / cif 来选中/删除/改写函数的内容
Plug 'kana/vim-textobj-user'
Plug 'kana/vim-textobj-indent'
Plug 'kana/vim-textobj-syntax'
Plug 'kana/vim-textobj-function', { 'for':['c', 'cpp', 'vim', 'java'] }
Plug 'sgur/vim-textobj-parameter'

"Vim-Signify
":SignifyDiff compare previous and current code splitly
Plug 'mhinz/vim-signify'

"SimpyFold
Plug 'tmhedberg/SimpylFold'

"Color Schemes
Plug 'sainnhe/sonokai'
Plug 'sainnhe/everforest'
Plug 'sonph/onehalf', {'rtp': 'vim'}
Plug 'jnurmine/Zenburn'
Plug 'altercation/vim-colors-solarized'
Plug 'joshdick/onedark.vim'
"Polyglot: A collection of language packs for Vim -- used for syntax
Plug 'sheerun/vim-polyglot'

"Airline: status bar with multi themes
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

"Let VIM check your syntax on each save
Plug 'vim-syntastic/syntastic'

"PEP 8 checking
Plug 'nvie/vim-flake8'

"File Tree
Plug 'preservim/nerdtree'
Plug 'Xuyuanp/nerdtree-git-plugin'
Plug 'ryanoasis/vim-devicons'
Plug 'tiagofumo/vim-nerdtree-syntax-highlight'
Plug 'PhilRunninger/nerdtree-buffer-ops'
Plug 'PhilRunninger/nerdtree-visual-selection'
"Tabs
Plug 'jistr/vim-nerdtree-tabs'
"hide .pyc files"
let NERDTreeIgnore=['\.pyc$', '\~$'] 
"ignore files in NERDTree
"Search basically anything by pressing ^P

"ctags and gutentags
"^] open definition in current tab
"^W ] open definition in new tab
"^W } open definition in preview split
Plug 'universal-ctags/ctags'
Plug 'ludovicchabant/vim-gutentags'

"AsyncRun 
Plug 'skywind3000/asyncrun.vim'

"CodeAnalysis
Plug 'dense-analysis/ale'

"Ycm
"Plug 'ycm-core/YouCompleteMe'
"Coc autocompile
Plug 'neoclide/coc.nvim', {'branch': 'release'}

call plug#end()            " required
filetype plugin indent on    " required

" Enable folding
set foldmethod=indent
set foldlevel=99

" Enable folding with the spacebar
nnoremap <space> za

au BufNewFile,BufRead *.py
    \ set tabstop=4|
    \ set softtabstop=4|
    \ set shiftwidth=4|
    \ set textwidth=79|
    \ set expandtab|
    \ set autoindent|
    \ set fileformat=unix

au BufNewFile,BufRead *.c, *.cpp
    \ set tabstop=4|
    \ set softtabstop=4|
    \ set shiftwidth=4|
    \ set textwidth=256|
    \ set expandtab|
    \ set autoindent|
    \ set fileformat=unix

au BufNewFile,BufRead *.js, *.html, *.css
    \ set tabstop=2|
    \ set softtabstop=2|
    \ set shiftwidth=2

"au BufRead,BufNewFile *.py,*.pyw,*.c,*.h match BadWhitespace /\s\+$/

set encoding=utf-8

"python with virtualenv support
"py << EOF
"import os
"import sys
"if 'VIRTUAL_ENV' in os.environ:
"  project_base_dir = os.environ['VIRTUAL_ENV']
"  activate_this = os.path.join(project_base_dir, 'bin/activate_this.py')
"  execfile(activate_this, dict(__file__=activate_this))
"EOF

"code highlight
let python_highlight_all=1
syntax on

if has('gui_running')
  set background=dark
  colorscheme solarized
  "Press F5 can switch between dark and light theme
else
  set t_Co=256
  set background=light
  set cursorline
"  colorscheme everforest
  colorscheme sonokai
  let g:everforest_background = 'hard'
  let g:airline_theme='sonokai'
" lightline
" let g:lightline = { 'colorscheme' : 'onehalfdark' }
endif
" TrueColor
if exists('+termguicolors')
  let &t_8f = "\<Esc>[38;2;%lu;%lu;%lum"
  let &t_8b = "\<Esc>[48;2;%lu;%lu;%lum"
  set termguicolors
endif
"Airline Statusbar Setting
"       96%   1165 
if !exists('g:airline_symbols')
let g:airline_symbols = {}
endif
let g:airline_left_sep=''
let g:airline_right_sep=''
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#show_splits = 0
let g:airline#extensions#tabline#show_buffers = 1
let g:airline#extensions#tabline#show_tab_count = 0
let g:airline#extensions#tabline#exclude_preview = 0
let g:airline#extensions#tabline#tab_nr_type = 1
let g:airline#extensions#tabline#show_tab_nr = 1
let g:airline#extensions#tabline#left_sep = ''
"let g:airline#extensions#tabline#left_alt_sep = ''
let g:airline#extensions#tabline#left_alt_sep = ''
let g:airlint_powerline_fonts = 0
let g:airline_symbols.linenr = ' '
let g:airline_symbols.maxlinenr = ' '
let g:airline_symbols.colnr = ': '
let g:airline_symbols.branch = ''
let g:airline#extensions#tabline#buffer_idx_mode = 1
 nmap <leader>1 <Plug>AirlineSelectTab1
 nmap <leader>2 <Plug>AirlineSelectTab2
 nmap <leader>3 <Plug>AirlineSelectTab3
 nmap <leader>4 <Plug>AirlineSelectTab4
 nmap <leader>5 <Plug>AirlineSelectTab5
 nmap <leader>6 <Plug>AirlineSelectTab6
 nmap <leader>7 <Plug>AirlineSelectTab7
 nmap <leader>8 <Plug>AirlineSelectTab8
 nmap <leader>9 <Plug>AirlineSelectTab9
 nmap <leader>0 <Plug>AirlineSelectTab0
 nmap <leader>- <Plug>AirlineSelectPrevTab
 nmap <leader>+ <Plug>AirlineSelectNextTab
let g:airline#extensions#tabline#keymap_ignored_filetypes =
        \ ['vimfiler', 'nerdtree']
let g:airline#extensions#tabline#buffer_nr_show = 1
let g:airline#extensions#tabline#formatter = 'unique_tail_improved'
let g:airline#extensions#tabline#buffer_min_count = 2
let g:airline#extensions#tabline#show_close_button = 0
let g:airline#extensions#tabline#close_symbol = 'X'
let airline#extensions#tabline#ignore_bufadd_pat =
             \ '\c\vgundo|undotree|vimfiler|tagbar|nerd_tree'
"let g:airline#extensions#ycm#enabled = 1
"let g:airline#extensions#ycm#error_symbol = 'E:'
"let g:airline#extensions#ycm#warning_symbol = 'W:'

"Line Numbering
set nu

au BufNewFile,BufRead *.markdown,*.mdown,*.mkd,*.mkdn,*.mdwn,*.md  set ft=markdown

nnoremap <leader>n :NERDTreeFocus<CR>
nnoremap <C-n> :NERDTree<CR>
nnoremap <C-t> :NERDTreeToggle<CR>
nnoremap <C-f> :NERDTreeFind<CR>

set showcmd

" Start NERDTree, unless a file or session is specified, eg. vim -S session_file.vim.
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists('s:std_in') && v:this_session == '' | NERDTree | endif

" Exit Vim if NERDTree is the only window remaining in the only tab.
autocmd BufEnter * if tabpagenr('$') == 1 && winnr('$') == 1 && exists('b:NERDTree') && b:NERDTree.isTabTree() | quit | endif

" If another buffer tries to replace NERDTree, put it in the other window, and bring back NERDTree.
autocmd BufEnter * if bufname('#') =~ 'NERD_tree_\d\+' && bufname('%') !~ 'NERD_tree_\d\+' && winnr('$') > 1 |
    \ let buf=bufnr() | buffer# | execute "normal! \<C-W>w" | execute 'buffer'.buf | endif

let NERDTreeHijackNetrw=1

"open split below and on right
set splitbelow
set splitright

"browse split windows easier
nnoremap <C-j> <C-w><C-j>
nnoremap <C-k> <C-w><C-k>
nnoremap <C-h> <C-w><C-h>
nnoremap <C-l> <C-w><C-l>

set tabstop=4
set shiftwidth=4
set expandtab

"Newline in INSERT mode
"nnoremap <M-o> $<CR>
"nnoremap <M-e> $
"7.15. YouCompleteMe                                            syntastic-ycm
"
""Syntastic can be used together with the "YouCompleteMe" Vim plugin (see
""https://github.com/ycm-core/YouCompleteMe). However, by default "YouCompleteMe"
""disables syntastic's checkers for the "c", "cpp", "objc", and "objcpp"
""filetypes, in order to allow its own checkers to run. If you want to use YCM's
""identifier completer but still run syntastic's checkers for those filetypes you
""have to set g:ycm_show_diagnostics_ui to 0. E.g.:
"let g:ycm_autoclose_preview_window_after_completion=1
"let g:ycm_show_diagnostics_ui = 0
"let g:ycm_add_preview_to_completeopt = 0
"let g:ycm_show_diagnostics_ui = 0
"let g:ycm_server_log_level = 'info'
"let g:ycm_min_num_identifier_candidate_chars = 2
"let g:ycm_collect_identifiers_from_comments_and_strings = 1
"let g:ycm_complete_in_strings=1
"let g:ycm_key_invoke_completion = '<c-x>'
""let g:ycm_extra_conf_globlist = [
""            \'/home/micuks/.vim/plugged/YouCompleteMe/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/examples/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/cs/testdata/testy-multiple-solutions/solution-not-named-like-folder/extra-conf-rel/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/cs/testdata/testy-multiple-solutions/solution-not-named-like-folder/extra-conf-bad/testy/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/cs/testdata/testy-multiple-solutions/solution-not-named-like-folder/extra-conf-abs/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/test-include/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/noflags/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/general_fallback/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/get_doc/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/client_data/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/driver_mode_cl/flag/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clang/testdata/driver_mode_cl/executable/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/clangd/testdata/extra_conf/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/language_server/testdata/project/settings_extra_conf/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/java/testdata/lombok_project/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/java/testdata/extra_confs/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/java/testdata/multiple_projects/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/testdata/extra_conf/project/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/ycmd/tests/testdata/client/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py',
""            \'/home/micuks/.vim/plugged/YouCompleteMe/python/ycm/tests/testdata/.ycm_extra_conf.py',
""            \]
"set completeopt=menu,menuone
"
"noremap <c-x> <NOP>
"
"let g:ycm_semantic_triggers =  {
"           \ 'c,cpp,python,java,go,erlang,perl': ['re!\w{2}'],
"           \ 'cs,lua,javascript': ['re!\w{2}'],
"           \ }

let g:vimspector_enable_mapping = 'HUMAN'

set autochdir

set clipboard=unnamed

"configure ctags
set tags=./.tags;,.tags

" gutentags 搜索工程目录的标志，碰到这些文件/目录名就停止向上一级目录递归
let g:gutentags_project_root = ['.root', '.svn', '.git', '.hg', '.project']

" 所生成的数据文件的名称
let g:gutentags_ctags_tagfile = '.tags'

" 将自动生成的 tags 文件全部放入 ~/.cache/tags 目录中，避免污染工程目录
let s:vim_tags = expand('~/.cache/tags')
let g:gutentags_cache_dir = s:vim_tags

" 配置 ctags 的参数
let g:gutentags_ctags_extra_args = ['--fields=+niazS', '--extra=+q']
let g:gutentags_ctags_extra_args += ['--c++-kinds=+px']
let g:gutentags_ctags_extra_args += ['--c-kinds=+px']

" 检测 ~/.cache/tags 不存在就新建
if !isdirectory(s:vim_tags)
   silent! call mkdir(s:vim_tags, 'p')
endif

"configure AsyncRun
" 自动打开 quickfix window ，高度为 6
let g:asyncrun_open = 12
" 任务结束时候响铃提醒
let g:asyncrun_bell = 1
" 设置 F10 打开/关闭 Quickfix 窗口
nnoremap <F10> :call asyncrun#quickfix_toggle(6)<cr>
"F9 compile single file
nnoremap <silent> <F9> :AsyncRun gcc -Wall -g "$(VIM_FILEPATH)" -o "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" -lstdc++ <cr>
"nnoremap <silent> <F9> :AsyncRun clangd --log=info "$(VIM_FILEPATH)" -o "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" <cr>
"F5 Run single file
nnoremap <silent> <F5> :AsyncRun -mode=term -pos=bottom -rows=10 -raw -cwd="$(VIM_FILEDIR)" "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" <cr>
"nnoremap <silent> <F5> :AsyncRun gdb "$(VIM_FILEDIR)/$(VIM_FILENOEXT)" <cr>
"search for project root dir
let g:asyncrun_rootmarks = ['.svn', '.git', '.root', '_darcs', 'build.xml'] 
"compile the project
nnoremap <silent> <F7> :AsyncRun -cwd=<root> make <cr>
"run the project
nnoremap <silent> <F8> :AsyncRun -cwd=<root> -raw make run <cr>
"test the project
nnoremap <silent> <F6> :AsyncRun -cwd=<root> -raw make test <cr>
"CMAKE update Makefile
nnoremap <silent> <F4> :AsyncRun -cwd=<root> cmake . <cr>

"Code Analysis
let g:ale_linters_explicit = 1
let g:ale_completion_delay = 500
let g:ale_echo_delay = 20
let g:ale_lint_delay = 500
let g:ale_echo_msg_format = '[%linter%] %code: %%s'
let g:ale_lint_on_text_changed = 'normal'
let g:ale_lint_on_insert_leave = 1
let g:airline#extensions#ale#enabled = 1

let g:ale_c_gcc_options = '-Wall -O2 -std=c99'
let g:ale_cpp_gcc_options = '-Wall -O2 -std=c++14'
let g:ale_c_cppcheck_options = ''
let g:ale_cpp_cppcheck_options = ''

let g:ale_sign_error = "\ue009\ue009"
hi! clear SpellBad
hi! clear SpellCap
hi! clear SpellRare
hi! SpellBad gui=undercurl guisp=red
hi! SpellCap gui=undercurl guisp=blue
hi! SpellRare gui=undercurl guisp=magenta

"LeaderF
let g:Lf_ShortcutF = '<c-p>'
let g:Lf_ShortcutB = '<m-n>'
noremap <c-n> :LeaderfMru<cr>
noremap <m-p> :LeaderfFunction!<cr>
noremap <m-n> :LeaderfBuffer<cr>
noremap <m-m> :LeaderfTag<cr>
let g:Lf_StlSeparator = { 'left': '', 'right': '', 'font': '' }

let g:Lf_RootMarkers = ['.project', '.root', '.svn', '.git']
let g:Lf_WorkingDirectoryMode = 'Ac'
let g:Lf_WindowHeight = 0.30
let g:Lf_CacheDirectory = expand('~/.vim/cache')
let g:Lf_ShowRelativePath = 0
let g:Lf_HideHelp = 1
let g:Lf_StlColorscheme = 'powerline'
let g:Lf_PreviewResult = {'Function':0, 'BufTag':0}

"enable <m-
let c='a'
while c <= 'z'
  exec "set <A-".c.">=\e".c
  exec "imap \e".c." <A-".c.">"
  let c = nr2char(1+char2nr(c))
endw

set timeout ttimeoutlen=50
