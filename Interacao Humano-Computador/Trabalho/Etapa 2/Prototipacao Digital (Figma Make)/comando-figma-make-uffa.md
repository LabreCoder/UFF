#PAPEL

Assuma a posição de um especialista em UI/UX com experiência em prototipação de alta fidelidade
Atue com foco em acessibilidade e design inclusivo para pessoas de diferentes idades e níveis de familiaridade digital
Atue também como redator UX (UX Writing), com experiência em textos curtos e botões de ação (CTAs) claros
Escreva todo o resultado em português do Brasil
----------------

#CONSIDERAÇÕES

Considere que o problema é a perda de objetos no Instituto de Computação (IC), no campus da Praia Vermelha da UFF, onde perder é comum e recuperar é raro, porque o objeto passa por várias pessoas sem registro e ninguém sabe onde entregar ou onde buscar.
Considere que a ideia principal da solução é um site acessível pelo celular, sem instalação, que registra o caminho do objeto (cadeia de custódia), mostra onde entregar e buscar, e devolve o item ao dono certo com prova de posse e recibo, sem burocratizar o uso.
Considere que a solução tem dois perfis no mesmo site: Comunidade (aluno, professor, servidor, quem perdeu e quem encontra) e Equipe (Portaria 01, Portaria 02 e Secretaria do IC).
Considere o questionário, que estou copiando a você no documento intitulado "Analise_questionario_Achados_e_Perdidos_UFF.pdf" (23 respostas). Os principais insights são: 11 de 23 perderam algo e só 4 recuperaram (todas garrafas; os documentos não voltaram); 16 de 23 não sabem ou não têm certeza de onde entregar um objeto achado; 21 de 23 dizem que saber onde procurar ou entregar ajudaria muito; 19 de 23 querem ver descrição e foto sem expor dados sensíveis; 10 de 14 que entregaram um objeto não sabem se ele chegou ao dono; 14 de 16 dão nota alta a confirmar características que só o dono saberia; 13 de 14 valorizam combinar a entrega em horário acessível; 13 de 17 valorizam ter um responsável claro; 16 de 23 preferem um site no celular sem instalação; acompanhar o status em detalhe é o recurso menos valorizado, então o aviso de status deve ser leve.
Considere as entrevistas com a Secretaria e as Portarias do IC, que estou copiando a você no documento intitulado "Relatório_Consolidado_de_Pesquisa_-_Achados_e_Perdidos.pdf" (5 participantes). Os principais insights são: nenhum recurso digital é usado hoje; o objeto recebe uma fita com data e local; a Portaria 01 guarda o item por cerca de 1 hora antes de levá-lo à Secretaria; a Portaria 02 repassa o item na hora; a devolução depende de o aluno "reconhecer e detalhar" o objeto, sem termo de saída; a Secretaria absorve a custódia sem que seja seu papel formal; o cadastro deve ter no máximo 3 cliques (foto, categoria, local); a equipe sugeriu QR code ou código curto, recibo de entrada e saída e registro do documento de quem retira; a tela pública deve mostrar o mínimo e manter os detalhes sob sigilo.
Considere o meu mapa de empatia, que estou copiando a você no documento intitulado "Mapa de Empatia", para entender o que as pessoas pensam, sentem, dizem e fazem diante do problema e refletir isso nos textos e no fluxo.
Considere as ideias do Crazy 4, que estou copiando a você no documento intitulado "crazy-4-uffa.md", apenas como inspiração. As ideias aproveitadas, já adaptadas à realidade, são: ponto central de custódia com atendente que entrega ao dono certo; pontos de entrega conhecidos; etiqueta com QR code no lugar da fita; aviso quando um "perdi" combina com um "achei"; divulgação do link nos grupos e cartazes; aviso de que o item foi devolvido para quem entregou. Pontos, ranking, prêmios, câmeras, robôs, drone, cães e viagem no tempo ficam fora do protótipo.
Considere a análise competitiva, que estou copiando a você no documento intitulado "Analise_Competitiva_v2.pdf". As ideias a aproveitar são: casos resolvidos como prova social (ACHUSP); integração com um canal que o aluno já usa e baixa fricção de acesso (Unicamp Serviços); mapa do campus com os pontos de ocorrência (Finder); aviso automático quando um "perdi" combina com um "achei" (Tinder); superar o grupo de WhatsApp oferecendo busca e histórico.
Considere prototipar a solução para as personas que estou copiando a você no documento intitulado "personas.pdf": Atendente da Secretaria (o custodiante), Porteiro (a triagem) e Aluno (o dono e quem encontra).
Considere prototipar a solução para os cenários que estou copiando a você no documento intitulado "cenarios.pdf": C1 Balcão cheio; C2 Troca de turno; C3 Sem saber onde procurar; C4 Item que repassa sem rastro; C5 Retirada sem comprovante; C6 Entregou e não soube o fim.
Considere as tarefas que estou copiando a você no documento intitulado "tarefas.pdf": cadastrar item em até 3 cliques; gerar etiqueta/QR code; registrar a retirada e gerar recibo de saída; delegar a custódia a um posto centralizador; emitir recibo de entrada; registrar o documento de quem retira; navegar pelo catálogo público; reivindicar um item; comprovar a posse; retirar o item.
Considere a prototipação em papel, que estou copiando a você no documento intitulado "prototipacao-em-papel-uffa.md". Ela define as 14 telas a serem geradas, os estados do item e os 7 fluxos de teste. Comunidade: A1 Início, A2 Pontos de entrega, A3 Catálogo, A4 Detalhe do item, A5 Provar posse, A6 Retirada, A7 Achei algo, A8 Perdi algo, A9 Meus registros. Equipe: S1 Cadastro rápido, S2 Itens em guarda, S3 Transferir item, S4 Pedidos de retirada, S5 Entregar e emitir recibo.
Considere que os estados do item são: Registrado, Em trânsito, Em guarda na Secretaria, Retirada solicitada, Retirado. Itens sem retirada seguem o destino definido pela instituição.
Considere que o catálogo público não mostra a foto real do objeto, por segurança, para evitar retirada por quem não é o dono. A foto e os detalhes ficam visíveis só para a Equipe. O catálogo público mostra categoria com ícone, local e data do achado e status.
Considere que a prova de posse é feita pelo dono, que descreve características que só ele saberia e informa a matrícula, antes de ver qualquer detalhe do item. A Equipe compara a descrição com o que registrou e decide entre aprovar, pedir mais detalhes ou recusar. Na retirada, a Equipe registra o documento de quem retira e emite o recibo de saída.
Considere que os dados reais das telas são: Campus da Praia Vermelha, Instituto de Computação (IC), Secretaria do IC, Portaria 01 (Prédio Principal) e Portaria 02 (Prédio Secundário).
----------------

#TAREFA

Crie para mim o prompt que eu vou utilizar para dar entrada no Figma Make para criar os protótipos através de inteligência artificial.
----------------

#RESTRIÇÕES

Estilo e layout
Interface em português do Brasil.
Site mobile-first, pensado para celular (cerca de 390 px de largura), com layout adaptado para tablet nas telas da Equipe (S1 a S5).
Aparência institucional, calma, organizada e confiável, sem cara de mural de classificados. Cantos levemente arredondados, bastante espaço em branco e um único foco de ação por tela.
Navegação simples: barra inferior com Início, Catálogo, Meus registros e Pontos de entrega para a Comunidade; para a Equipe, barra com Novo item, Itens em guarda e Pedidos.
Mostrar um seletor de perfil (Comunidade ou Equipe) apenas para a demonstração do protótipo.

Paleta de cores e fontes (identidade do portfólio UFFa)
Fundo geral: #F7F4EE. Texto principal e títulos: #0A1828. Botões primários: #004B57 com texto branco. Variação escura para pressionado: #003F5D. Acentos e ícones: #178582 e #4A9C99. Superfícies de apoio: #E7EFED. Divisores e detalhes: #BFA181. Destaque pontual: #E8E337 com texto #0A1828. Sucesso: #39E75F com texto #0A1828. Erro e recusa: #E74C3C, sempre com ícone e texto.
Fonte de títulos: DM Serif Display. Fonte de textos: DM Sans. Usar Georgia e system-ui como alternativas.
Usar texto branco apenas sobre #004B57 ou #003F5D. Não usar texto branco sobre #178582, #4A9C99, #39E75F, #E8E337 ou #E74C3C.

Princípios de Gestalt
Proximidade: agrupar campos e informações relacionados. Similaridade: botões, cartões e selos de status iguais para ações iguais. Continuidade: fluxos em linha vertical e linha do tempo do item. Figura e fundo: cartões claros sobre o fundo #F7F4EE. Hierarquia visual: um título, um destaque e um botão primário por tela.

Acessibilidade
Texto com 16 px ou mais; contraste mínimo de 4,5:1 para texto normal e 3:1 para textos grandes e ícones. Áreas de toque de 44 px ou mais. Ícone sempre acompanhado de texto. Status nunca indicado só por cor: usar cor, ícone e texto juntos. Nenhuma ação que dependa só de gesto, como deslizar. Linguagem simples, sem siglas e sem jargão. Foco visível, ordem de leitura lógica e rótulos claros nos campos.

Limites do escopo
Gerar somente as 14 telas listadas em considerações, com navegação clicável entre elas conforme os 7 fluxos: F1 aluno acha um objeto e entrega; F2 porteiro recebe e cadastra; F3 troca de turno entre Portaria e Secretaria; F4 atendente recebe no balcão cheio; F5 dono encontra o item e retira; F6 aluno perdeu algo e recebe aviso; F7 aluno acompanha o que entregou.
Basear-se unicamente nos arquivos fornecidos. Não criar informações adicionais. Quando um dado não existir nos arquivos, como horário de atendimento, nome do responsável ou número de itens devolvidos, mostrar o campo com o texto "A informar".

O que deve ser usado na interface
Ícones de categoria no lugar da foto real nas telas públicas. QR code ou código curto no item e no pedido (exemplo de formato: UFFA-0142). Linha do tempo do item. Selos de status com ícone e texto. Botões grandes e textos curtos. Aviso de que a foto e a descrição ficam guardadas com a Equipe.

O que não deve ser usado na interface
Nenhuma foto real de objeto nas telas públicas. Nenhum chat ou mensagem entre usuários. Nenhum ponto, ranking, XP, cupom ou prêmio. Nenhum mapa com GPS ou rastreio em tempo real. Nenhuma câmera, IA, drone ou robô. Nenhum login social. Nenhuma exibição de nome, número de documento ou telefone de pessoas no catálogo público. Nenhum texto longo.
----------------

#FORMATO

Quero um texto único, em português, que será um prompt para ser colado no Figma Make, sem comentários antes ou depois.
O texto deve ser organizado em seções: contexto do produto; identidade visual; regras de acessibilidade e de UX Writing; lista das 14 telas, cada uma com objetivo, conteúdo, textos dos botões e para onde cada ação leva; fluxos navegáveis; restrições.
----------------

#CRITÉRIOS DE QUALIDADE

O prompt deve ter detalhes suficientes para que eu não precise adicionar mais nada.
O prompt deve usar como base todo o material fornecido e manter a ligação entre cada tela e os dados da pesquisa.
O prompt deve estar em português.
Aplicar os princípios de design e as regras de UX Writing e CTAs da aula 11: hierarquia visual, consistência, simplicidade, feedback a cada ação, prevenção de erros e reconhecimento em vez de memorização.
Botões com verbo de ação e resultado claro, por exemplo "Achei algo", "Perdi algo", "Quero retirar", "Enviar pedido" e "Entregar e gerar recibo". Mensagens curtas, em voz ativa, sem culpar a pessoa e com orientação do próximo passo. Mensagens de erro dizem o que aconteceu e como resolver.
A interface deve ser compreensível para um aluno com pressa, um professor ou servidor e um atendente com o balcão cheio, sem treinamento prévio.
----------------

#EXEMPLOS

Considere como exemplos e inspiração:
ACHUSP: seção pública de casos resolvidos como prova social. Aproveitar a ideia, mostrando o número de itens devolvidos quando houver dado real.
Unicamp Serviços: achados e perdidos dentro de um canal que o aluno já usa, com baixa fricção. Aproveitar a ideia de acesso por link e QR code, sem instalação.
UniFind: fluxo claro de postar item e explorar achados. Evitar o contato direto entre usuários.
Perdi Mas Achei: pioneiro nacional. Evitar os problemas relatados de ícones pequenos e listagem sem filtro.
Finder (IFSP Hortolândia): mapa do campus com pontos de ocorrência. Aproveitar a ideia de forma simples, com os pontos de entrega do IC.
Grupos de WhatsApp e Facebook: concorrência real. Oferecer o que eles não têm, que é busca e histórico.
Facebook Marketplace e OLX: servem de contraste, por misturarem achados com vendas e não terem verificação de dono.
Tinder: aviso automático quando um "perdi" combina com um "achei", sem expor detalhes do item.
Waze: confirmação colaborativa. Não aproveitar nesta versão, porque o status do item é controlado pela Equipe.
----------------
