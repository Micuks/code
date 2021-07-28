set nocompatible              " required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

" let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'

" add all your plugins here (note older versions of Vundle
" used Bundle instead of Plugin)

" ...
" SimpyFold
Plugin 'tmhedberg/SimpylFold'
"Debug: VimSpector
Plugin 'puremourning/vimspector'

"indentpython
"Plugin 'vim-scripts/indentpython.vim'

"Color Schemes
Plugin 'sainnhe/sonokai'
Plugin 'sainnhe/everforest'
Plugin 'sonph/onehalf', {'rtp': 'vim'}
Plugin 'jnurmine/Zenburn'
Plugin 'altercation/vim-colors-solarized'
Plugin 'joshdick/onedark.vim'
"Polyglot: A collection of language packs for Vim -- used for syntax
Plugin 'sheerun/vim-polyglot'

"Perform basic git commands without leaving the VIM environment
Plugin 'tpope/vim-fugitive'

"Powerline: status bar
"Plugin 'Lokaltog/powerline', {'rtp': 'powerline/bindings/vim/'}
"Airline: status bar with multi themes
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'

"Let VIM check your syntax on each save
Plugin 'vim-syntastic/syntastic'

"PEP 8 checking
Plugin 'nvie/vim-flake8'

"File Tree
Plugin 'scrooloose/nerdtree'
"Tabs
Plugin 'jistr/vim-nerdtree-tabs'
"hide .pyc files"let NERDTreeIgnore=['\.pyc$', '\~$'] "ignore files in NERDTree
"Search basically anything by pressing ^P
Plugin 'kien/ctrlp.vim'

"AutoPairs
Plugin 'jiangmiao/auto-pairs'

"cpp-enhanced-highlight
"Plugin 'octol/vim-cpp-enhanced-highlight'

"Auto completion for python
"Plugin 'davidhalter/jedi-vim'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

"AutoComplete
Bundle 'Valloric/YouCompleteMe'

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

let g:ycm_autoclose_preview_window_after_completion=1
map <leader>g  :YcmCompleter GoToDefinitionElseDeclaration<CR>

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
let g:airline#extensions#ycm#enabled = 1
let g:airline#extensions#ycm#error_symbol = 'E:'
let g:airline#extensions#ycm#warning_symbol = 'W:'

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
"Syntastic can be used together with the "YouCompleteMe" Vim plugin (see
"https://github.com/ycm-core/YouCompleteMe). However, by default "YouCompleteMe"
"disables syntastic's checkers for the "c", "cpp", "objc", and "objcpp"
"filetypes, in order to allow its own checkers to run. If you want to use YCM's
"identifier completer but still run syntastic's checkers for those filetypes you
"have to set g:ycm_show_diagnostics_ui to 0. E.g.:
let g:ycm_show_diagnostics_ui = 0

let g:vimspector_enable_mapping = 'HUMAN'
