-- Aula 2 - Arquitetura Física e Buffer Pool
DROP TABLE IF EXISTS pedidos;

CREATE TABLE pedidos (
    id          INTEGER PRIMARY KEY,
    cliente_id  INTEGER NOT NULL,
    valor       NUMERIC(10,2) NOT NULL,
    criado_em   TIMESTAMP NOT NULL DEFAULT now()
);

INSERT INTO pedidos (id, cliente_id, valor)
SELECT gs,
       (random() * 5000)::INT,
       (random() * 1000)::NUMERIC(10,2)
FROM generate_series(1, 200000) AS gs;

ANALYZE pedidos;
