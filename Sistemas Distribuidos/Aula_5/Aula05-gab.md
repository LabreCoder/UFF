1. If a client and a server are placed far apart, we may see network latency  
   dominating overall performance. How can we tackle this problem?  
     
   It really depends on how the client is organized. It may be possible to divide the client-side code into smaller parts that can run separately. In that case, when one part is waiting for the server to respond, we can schedule another part. Alternatively, we may be able to rearrange the client so that it can do other work after having sent a request to the server. This last solution effectively replaces the synchronous  client-server communication with asynchronous one-way communication.  
     
2. What is a three-tiered client-server architecture?  
     
   A three-tiered client-server architecture consists of three logical layers, where each layer is, in principle, implemented at a separate machine. The highest layer consists of a client user interface, the middle layer contains the actual application, and the lowest layer implements the data that are being used.

3. Consider a chain of processes P1, P2, ..., Pn implementing a multitiered client-server architecture. Process Pi is client of process Pi+1, and Pi will return a reply to Pi−1 only after receiving a reply from Pi+1. What are the main problems with this organization when taking a look at the request-reply performance at process P1?  
     
   Performance can be expected to be bad for large n. The problem is that each communication between two successive layers is, in principle, between two different machines. Consequently, the performance between P1 and P2 may also be determined by n − 2 request-reply interactions between the other layers. Another problem is that if one machine in the chain performs badly or is even temporarily unreachable, then this will immediately degrade the performance at the highest level.  
     
4. In a structured overlay network, messages are routed according to the  
   topology of the overlay. What is an important disadvantage of this approach?  
     
   The problem is that we are dealing only with logical paths. It may very well be the case that two nodes A and B which are neighbors in the overlay network are  physically placed far apart. As a consequence, the logically short path between A and B may require routing a message along a very long path in the underlying physical network.  
     
5. Not every node in a peer-to-peer network should become superpeer. What  
   are reasonable requirements that a superpeer should meet?  
     
   In the first place, the node should be highly available, as many other nodes rely on it. Also, it should have enough capacity to process requests. Most important perhaps is that fact that it can be trusted to do its job well.  
     
6. Diferencie estilo arquitetônico de arquitetura de sistema.  
     
   Estilo arquitetônico  
   Organização lógica do conjunto de componentes  
   Diz como vários componentes de software devem ser organizados e interagir  
   Arquitetura de sistema  
   Organização física dos componentes  
     
     
7. Quais as vantagens e desvantagens do estilo arquitetônico organizado em camadas?  
     
   VANTAGENS  
   Simplicidade  
   Acesso a dados centralizado

   Segurança

   Separação de responsabilidades  
     
   DESVANTAGENS  
   Não é escalável  
   Extensibilidade limitada  
   Modularidade do código está na subdivisão em pacotes, não em camadas  
   A camada pode se tornar grande e complexa com o tempo, com alto acoplamento  
   Implantação lenta  
     
8. Quais as vantagens e desvantagens do estilo arquitetônico orientado a serviços?  
     
   VANTAGENS  
   Escalabilidade  
   Reuso  
   Implantação ágil  
   Extensibilidade  
   Modularização por meio de serviços  
   Flexibilidade  
   Coexistência de vários stacks tecnológicos  
     
   DESVANTAGENS  
   Configuração e manutenção complexas  
   Complexidade cada vez maior com o aumento do número de serviços  
   Maior latência de comunicação  
     
9. Explique o estilo arquitetônico baseado em recursos  
     
   Visão do SD como um coleção de recursos que são individualmente gerenciados por componentes de software. Recursos podem ser remotamente adicionados, removidos, modificados e recuperados, e cada componente suporta essas 4 operações (REST \- Representational State Transfer). A interface é definida em função do formato dos dados enviados e recebidos e os componentes não retêm estado.  
     
   Muito conveniente para trabalhar na web com o protocolo HTTP porque a Web é centrada em dados, cada um com um identificador único (URI), e o protocolo HTTP suporta esses 4 verbos: GET, POST, DELETE, UPDATE.  
     
     
10. O que é um serviço em estilos arquitetônicos?  
      
    O serviço em si é uma entidade autocontida que pode ser uma função ou um conjunto de classes que oferecem uma funcionalidade. Ele aparece como uma unidade para o mundo exterior e possui e requer interfaces bem definidas, expressas por meio de contratos, sem revelar a sua implementação. Serviços podem compor e serem compostos por outros serviços. oferecendo reuso e baixo acoplamento.  
      
11. Qual a diferença entre distribuição vertical e horizontal?  
      
    A distribuição vertical divide componentes logicamente diferentes  (ex. cada camada da arquitetura em camadas) em máquinas diferentes, enquanto a distribuição horizontal divide componentes logicamente equivalentes (ex. várias instâncias de um mesmo serviço na arquitetura orientada a serviços) em máquinas diferentes.  
      
12. O que é um cliente magro?  
      
    É um processo cliente que desempenha poucas funcionalidades e consome poucos recursos computacionais. É ideal quando a máquina cliente possui baixa capacidade de processamento e armazenamento para a aplicação e comunicação em rede de alta velocidade. É o caso de aplicativos móveis, que executam em nós com baixo poder computacional.  
      
13. Diferencie os servidores quanto à manutenção de estado.  
      
    Sem estado: não mantém informações sobre o estado de seus clientes.  
    Estado flexível: mantém dados por tempo limitado.  
    Com estado: mantém informações persistentes sobre o cliente.  
      
14. O que é uma rede de sobreposição?  
      
    Rede na qual os nós são os processos e os enlaces representam os canais de comunicação possíveis.  
      
15. Diferencie arquitetura peer-to-peer estruturada e não=estruturada.  
      
    A arquitetura peer-to-peer estruturada consiste de uma rede de sobreposição construída com a utilização de um procedimento determinístico que permite a cada nó saber qual outro nó possui o item de dado desejado. Já a rede peer-to-peer não-estruturada consiste de uma rede de sobreposição que forma um grafo aleatório. Nesse caso, a consulta por um item dado é feita inundando a rede com uma mensagem de busca por qual nó possui o item de dado.  
      
16. Explique como funciona a inundação de rede.  
      
    Um nó emissor 𝑢 simplesmente passa uma solicitação por um item de dados para todos os seus vizinhos. Um nó receptor 𝑣 ignora a solicitação caso já a tenha visto antes. Caso contrário, 𝑣 busca localmente o item de dados solicitado. Se 𝑣 tiver os dados necessários, ele pode responder diretamente ao nó emissor 𝑢 ou enviá-lo de volta ao encaminhador original, que então o devolverá ao encaminhador anterior, e assim por diante.  Se 𝑣 não possuir os dados solicitados, ele encaminha a solicitação para todos os seus próprios vizinhos. Um valor de tempo de vida ou TTL  (time-to-live) define o número máximo de saltos que uma solicitação pode realizar ao ser encaminhada para reduzir o número de mensagens na rede.  
      
    