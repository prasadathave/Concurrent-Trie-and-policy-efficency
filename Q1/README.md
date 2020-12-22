Here Trie.h is auxilary and Trie.c contains all the code.
test_trie.c files are basically tesing different locking techniques and their efficiency.
python files are for making plots.
## Compiling the test code:
- **Single Threaded:** `make test_trie_single_threaded`
- **Multi Threaded (Single Locking):** `make test_trie_s_lock` 
- **Multi Threaded (R/W Lock):** `make test_trie_rw_lock`
- **Multi Threaded (Hand on Hand Lock):** `make test_trie_hoh_lock`

## Compiling and running the tests:
- **Single Threaded:** `make single_threaded`
- **Multi Threaded (Single Locking):** `make s_lock` 
- **Multi Threaded (R/W Lock):** `make rw_lock`
- **Multi Threaded (Hand on Hand Lock):** `make hoh_lock`
