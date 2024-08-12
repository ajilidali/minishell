# Rapport d'Erreurs

---

## 1. builtins

**Test 21:**

- **Erreur:** `echo $?HELLO`
- **Code de sortie:** 0
- **Erreur mini:** ( )
- **Erreur bash:** (0HELLO)

---

**Test 40:**

- **Erreur:** `cd $PWD hi`
- **Code de sortie mini:** 0
- **Code de sortie bash:** 1
- **Erreur mini:** (too many arguments)
- **Erreur bash:** (too many arguments)

---

**Test 41:**

- **Erreur:** `cd 123123`
- **Code de sortie mini:** ``
- **Code de sortie bash:** 1
- **Erreur mini:** (DEDSEC: cd: 123123: No such file or directory)
- **Erreur bash:** (No such file or directory)

---

**Test 50:**

- **Erreur:** `exit hello`
- **Code de sortie mini:** 1
- **Erreur mini:** (exit numeric argument required)
- **Erreur bash:** (numeric argument required)

---

**Test 55:**

- **Erreur:** `cat minishell.h | grep ");"$`
- **Code de sortie mini:** 2
- **Code de sortie bash:** 1
- **Erreur mini:** (No such file or directory No such file or directory)
- **Erreur bash:** (No such file or directory)

---

**Test 61:**

- **Erreur:** `echo <"./test_files/infile" "bonjour 42"`
- **Code de sortie mini:** ``
- **Code de sortie bash:** ``
- **Erreur mini:** ( )
- **Erreur bash:** (bonjour 42)

---

**Test 68:**

- **Erreur:** `echo <"./test_files/infile_big" | cat <"./test_files/infile"`
- **Code de sortie mini:** |
- **Code de sortie bash:** hi hello world 42
- **Erreur mini:** ( | cat < ./test_files/infile)
- **Erreur bash:** (hi hello world 42)

---

**Test 73:**

- **Erreur:** `cat <"./test_files/infile" | echo hi`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory)
- **Erreur bash:** (Broken pipe)

---

**Test 75:**

- **Erreur:** `cat <"./test_files/infile_big" | echo hi`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory)
- **Erreur bash:** (Broken pipe)

---

**Test 87:**

- **Erreur:** `ls >"./outfiles/outfile""1""2""3""4""5"`
- **Code de sortie mini:** ``
- **Code de sortie bash:** 1
- **Erreur mini:** (Only in ./mini_outfiles: outfile)
- **Erreur bash:** (Only in ./bash_outfiles: outfile12345)

---

**Test 90:**

- **Erreur:** `cat <"./test_files/infile" >"./outfiles/outfile01"`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory No such file or directory)
- **Erreur bash:** ( )

---

**Test 93:**

- **Erreur:** `echo hi | echo >./outfiles/outfile01 bye`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ)
- **Erreur bash:** (bye)

---

**Test 94:**

- **Erreur:** `echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (Files ./mini_outfiles/outfile02 and ./bash_outfiles/outfile02 differ)
- **Erreur bash:** (bye)

---

**Test 96:**

- **Erreur:** `echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye`
- **Code de sortie mini:** ``
- **Code de sortie bash:** ``
- **Erreur mini:** ( )
- **Erreur bash:** ( )

---

## 2. pipes

**Test 55:**

- **Erreur:** `cat minishell.h | grep ");"$`
- **Code de sortie mini:** 2
- **Code de sortie bash:** 1
- **Erreur mini:** (No such file or directory No such file or directory)
- **Erreur bash:** (No such file or directory)

---

**Test 68:**

- **Erreur:** `echo <"./test_files/infile_big" | cat <"./test_files/infile"`
- **Code de sortie mini:** |
- **Code de sortie bash:** hi hello world 42
- **Erreur mini:** ( | cat < ./test_files/infile)
- **Erreur bash:** (hi hello world 42)

---

**Test 73:**

- **Erreur:** `cat <"./test_files/infile" | echo hi`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory)
- **Erreur bash:** (Broken pipe)

---

**Test 75:**

- **Erreur:** `cat <"./test_files/infile_big" | echo hi`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory)
- **Erreur bash:** (Broken pipe)

---

**Test 93:**

- **Erreur:** `echo hi | echo >./outfiles/outfile01 bye`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ)
- **Erreur bash:** (bye)

---

**Test 94:**

- **Erreur:** `echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (Files ./mini_outfiles/outfile02 and ./bash_outfiles/outfile02 differ)
- **Erreur bash:** (bye)

---

## 3. redirects

**Test 61:**

- **Erreur:** `echo <"./test_files/infile" "bonjour 42"`
- **Code de sortie mini:** ``
- **Code de sortie bash:** ``
- **Erreur mini:** ( )
- **Erreur bash:** (bonjour 42)

---

**Test 68:**

- **Erreur:** `echo <"./test_files/infile_big" | cat <"./test_files/infile"`
- **Code de sortie mini:** |
- **Code de sortie bash:** hi hello world 42
- **Erreur mini:** ( | cat < ./test_files/infile)
- **Erreur bash:** (hi hello world 42)

---

**Test 73:**

- **Erreur:** `cat <"./test_files/infile" | echo hi`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory)
- **Erreur bash:** (Broken pipe)

---

**Test 75:**

- **Erreur:** `cat <"./test_files/infile_big" | echo hi`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory)
- **Erreur bash:** (Broken pipe)

---

**Test 87:**

- **Erreur:** `ls >"./outfiles/outfile""1""2""3""4""5"`
- **Code de sortie mini:** ``
- **Code de sortie bash:** 1
- **Erreur mini:** (Only in ./mini_outfiles: outfile)
- **Erreur bash:** (Only in ./bash_outfiles: outfile12345)

---

**Test 90:**

- **Erreur:** `cat <"./test_files/infile" >"./outfiles/outfile01"`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (No such file or directory No such file or directory)
- **Erreur bash:** ( )

---

**Test 93:**

- **Erreur:** `echo hi | echo >./outfiles/outfile01 bye`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (Files ./mini_outfiles/outfile01 and ./bash_outfiles/outfile01 differ)
- **Erreur bash:** (bye)

---

**Test 94:**

- **Erreur:** `echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 0
- **Erreur mini:** (Files ./mini_outfiles/outfile02 and ./bash_outfiles/outfile02 differ)
- **Erreur bash:** (bye)

---

## 4. divers

**Test 133:**

- **Erreur:** `$PWD`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 1
- **Erreur mini:** (Permission denied)
- **Erreur bash:** (Is a directory)

---

**Test 135:**

- **Erreur:** `$EMPTY echo hi`
- **Code de sortie mini:** ``
- **Code de sortie bash:** 0
- **Erreur mini:** ( )
- **Erreur bash:** (hi)

---

**Test 136:**

- **Erreur:** `./test_files/invalid_permission`
- **Code de sortie mini:** 127
- **Code de sortie bash:** 126
- **Erreur mini:** (Permission denied)
- **Erreur bash:** (Permission denied)

---

**Test 138:**

- **Erreur:** `missing.out`
- **Code de sortie mini:** 1
- **Code de sortie bash:** 127
- **Erreur mini:** (No such file or directory)
- **Erreur bash:** (command not found)

---