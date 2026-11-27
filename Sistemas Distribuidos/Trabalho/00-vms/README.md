# 00-vms — demonstração em máquinas virtuais (VirtualBox)

Extra opcional: roda o trabalho em **duas VMs Ubuntu Server** (rede real entre elas) em vez de só containers na mesma máquina.

```
VM sd-servidor  192.168.56.10  (2,5 GB RAM)   servidores: gRPC (porta 8102), ...
VM sd-cliente   192.168.56.11  (1,5 GB RAM)   clientes Python e Node.js
rede host-only vboxnet0 192.168.56.0/24 (o host é 192.168.56.1)
```

## Scripts (ficam em `~/vm-sd/` na máquina do aluno)
| Arquivo | Para que serve |
|---|---|
| `criar-vm.sh` | Cria a VM **sem ligar**, com limites rígidos (RAM ≤ 2560 MB, ≤ 2 CPUs, disco dinâmico ≤ 25 GB, soma das VMs ≤ 5000 MB), confere o SHA256 da ISO e prepara a instalação automática |
| `user-data.template` | Autoinstall do Ubuntu: SSH com chave, IP fixo na rede host-only, Docker + Compose |
| `watchdog.sh` | **Vigia**: desliga as VMs `sd-*` se a RAM livre do host < 1,8 GB, disco < 15 GB, VM `aborted/stuck`, disco virtual > 26 GB ou tempo limite |
| `iniciar.sh` | Liga uma VM **sempre com o vigia ativo** (recusa ligar se o vigia não subiu) |

## Passo a passo
1. ISO oficial **Ubuntu Server 24.04.5** de `releases.ubuntu.com`, conferida com `SHA256SUMS` + assinatura GPG (`SHA256SUMS.gpg`, chave `8439 38DF 228D 22F7 B374 2BC0 D94A A3F0 EFE2 1092`), em `~/vm-sd/iso/`.
2. Rede: `VBoxManage hostonlyif create` e `VBoxManage hostonlyif ipconfig vboxnet0 --ip 192.168.56.1 --netmask 255.255.255.0`.
3. Chave SSH: `ssh-keygen -t ed25519 -N "" -f ~/.ssh/id_ed25519_sd`; senha local em `~/vm-sd/.senha-vm` (usuário `sd`).
4. `./criar-vm.sh sd-servidor 2560 2 20 192.168.56.10` e `./criar-vm.sh sd-cliente 1536 1 12 192.168.56.11`.
5. `./iniciar.sh sd-servidor 120` (instalação automática, ~10 min; depois reinicia sozinha), idem `sd-cliente`.
6. Copiar o projeto: `tar -cf - . | ssh -i ~/.ssh/id_ed25519_sd sd@192.168.56.10 'mkdir ~/grpc && tar -xf - -C ~/grpc'` (nas duas VMs) e `docker compose up -d --build servidor` na VM servidor / `docker compose build` na VM cliente.
7. Demo (no host): `02-grpc/demo-vms.sh`.

## O que a demo em VMs mostra a mais
- Chamada gRPC **pela rede** entre duas máquinas; cliente Python e Node.js contra o mesmo servidor.
- **Falha A** (`docker stop` no servidor): erro `UNAVAILABLE` *imediato* — o cliente sabe que falhou.
- **Falha B** (`VBoxManage controlvm sd-servidor setlinkstate2 off`, "puxar o cabo"): silêncio; o cliente só descobre pelo keepalive/prazo. Mostra que, em sistemas distribuídos, "caiu" e "lento" são indistinguíveis.
- Recuperação: o canal passa por `TRANSIENT_FAILURE` e volta a `READY` (ver `02-grpc/vms/sonda.py`).

## Cuidados (por que existe o vigia)
Host com 14 GB de RAM e swap quase cheia. O vigia protege RAM e disco; ele já desligou uma VM sozinho ao detectar swap cheia com pouca RAM.
Parar tudo: `VBoxManage controlvm sd-servidor poweroff` e `VBoxManage controlvm sd-cliente poweroff`.
