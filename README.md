# MECSOL

## BASICO:

- Git para Windows: https://phoenixnap.com/kb/how-to-install-git-windows -- Para Quem Esta Desenvolvendo 
- MINGW para Windows: https://www.youtube.com/watch?v=sXW2VLrQ3Bs (Compilador De C) -- Para Todos
- Depois de baixar MINGW, abra o CMD e escreva "mingw-get install mingw32-make" (Facilita a compilação devido ao script dentro do Makefile) -- Para Todos
- Depois de baixar o "mingw32-make", vá para C:/MINGW/bin e ache "mingw32-make.exe" e altere o nome para "make.exe" -- Para Todos (Ao invés de digitar "mingw32-make" no CMD para compilar, iremos digitar apenas "make" )

## Usando o MakeFile
1. Abra o CMD, e escreva "cd Desktop" e depois "cd MECSOL"
2. Para compilar digite "make" no CMD, e o executável mathi.exe será compilado :) 
3. Tenho que completar para explicar como funciona a MakeFile, mas apriori crie sempre um arquivo ".c" e ".h" com o mesmo nome
4. No MakeFile escreva "seu_arquivo.o" na linha que tenha escrito "OBJECTS =" e escreva ele após o "=" e espaçado dos outros ".o"
5. Após isso, salve e digite no CMD "make"
5. Digite no CMD "make clean" para limpar os ".o" e o ".exe" antes de subir para o GitHub :) 


## Para Quem Está Desenvolvendo
### Usando Git:

1. Abra o CMD, e escreva "cd Desktop"
2. Escreva "git clone https://github.com/RemeLards/MECSOL.git", para clonar o Diretório para seu computador
3. Após fazer alterações no código, abra o CMD e escreva  "cd Desktop" e "cd MECSOL", se estiver usando VSCode,
  exclua a pasta ".vscode" e tudo que ela tenha com "del .vscode" dentro do diretório
4. Escreva no CMD "git add ." (adiciona todos os arquivos alterados para a fila de upload)
5. Escreva no CMD "git status" para ver quais arquivos novos e/ou quais arquivos alterados você fez mudanças (se tive a pasta .vscode exclua ela e repita tudo a partir do passo 4) 
6. Escreva no CMD "git commit -m "mensagem" ", a mensagem deve descrever algo que você fez, como uma alteração em tal arquivo, adição e modificação de funções
7. Após tudo isso, escreva no CMD "git push" para subir as suas alterações para este repositório do GitHub
8. Para atualizar a pasta como o código mais novo abra o CMD, e escreva "cd Desktop" e depois "cd MECSOL", após isso escreva "git pull"

