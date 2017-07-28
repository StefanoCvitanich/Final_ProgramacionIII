--
-- PostgreSQL database dump
--

-- Dumped from database version 9.5.3
-- Dumped by pg_dump version 9.5.3

SET statement_timeout = 0;
SET lock_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET search_path = public, pg_catalog;

--
-- Name: HighScores_ID_HS_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "HighScores_ID_HS_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "HighScores_ID_HS_seq" OWNER TO postgres;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: HighScores; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE "HighScores" (
    "ID_HS" integer DEFAULT nextval('"HighScores_ID_HS_seq"'::regclass) NOT NULL,
    "Juego" integer,
    "Jugador" integer,
    "Puntuacion" integer
);


ALTER TABLE "HighScores" OWNER TO postgres;

--
-- Name: Juegos_ID_Juego_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Juegos_ID_Juego_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "Juegos_ID_Juego_seq" OWNER TO postgres;

--
-- Name: Juegos; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE "Juegos" (
    "ID_Juego" integer DEFAULT nextval('"Juegos_ID_Juego_seq"'::regclass) NOT NULL,
    "Nombre_Juego" text NOT NULL,
    "Descripcion_Juego" text
);


ALTER TABLE "Juegos" OWNER TO postgres;

--
-- Name: Jugadores_ID_Jugador_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "Jugadores_ID_Jugador_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "Jugadores_ID_Jugador_seq" OWNER TO postgres;

--
-- Name: Jugadores; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE "Jugadores" (
    "ID_Jugador" integer DEFAULT nextval('"Jugadores_ID_Jugador_seq"'::regclass) NOT NULL,
    "Username" text,
    "Password" text
);


ALTER TABLE "Jugadores" OWNER TO postgres;

--
-- Name: RegistroDeUso_ID_Registro_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "RegistroDeUso_ID_Registro_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "RegistroDeUso_ID_Registro_seq" OWNER TO postgres;

--
-- Name: RegistroDeUso; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE "RegistroDeUso" (
    "ID_Registro" integer DEFAULT nextval('"RegistroDeUso_ID_Registro_seq"'::regclass) NOT NULL,
    "Juego" integer,
    "Jugador" integer,
    "Fecha/Hora" timestamp with time zone
);


ALTER TABLE "RegistroDeUso" OWNER TO postgres;

--
-- Name: SavedGames_ID_SavedGame_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE "SavedGames_ID_SavedGame_seq"
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE "SavedGames_ID_SavedGame_seq" OWNER TO postgres;

--
-- Name: SavedGames; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE "SavedGames" (
    "ID_SavedGame" integer DEFAULT nextval('"SavedGames_ID_SavedGame_seq"'::regclass) NOT NULL,
    "Fecha/Hora" timestamp with time zone,
    "Nombre_Partida" text,
    "Data" text,
    "Juego" integer,
    "Jugador" integer
);


ALTER TABLE "SavedGames" OWNER TO postgres;

--
-- Data for Name: HighScores; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "HighScores" ("ID_HS", "Juego", "Jugador", "Puntuacion") FROM stdin;
\.


--
-- Name: HighScores_ID_HS_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"HighScores_ID_HS_seq"', 1, false);


--
-- Data for Name: Juegos; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Juegos" ("ID_Juego", "Nombre_Juego", "Descripcion_Juego") FROM stdin;
2	Burning Sands	Un juego muy copado
\.


--
-- Name: Juegos_ID_Juego_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Juegos_ID_Juego_seq"', 3, true);


--
-- Data for Name: Jugadores; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "Jugadores" ("ID_Jugador", "Username", "Password") FROM stdin;
1	Sonny	1234
2	Pepe	1010
\.


--
-- Name: Jugadores_ID_Jugador_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"Jugadores_ID_Jugador_seq"', 2, true);


--
-- Data for Name: RegistroDeUso; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "RegistroDeUso" ("ID_Registro", "Juego", "Jugador", "Fecha/Hora") FROM stdin;
\.


--
-- Name: RegistroDeUso_ID_Registro_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"RegistroDeUso_ID_Registro_seq"', 1, false);


--
-- Data for Name: SavedGames; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY "SavedGames" ("ID_SavedGame", "Fecha/Hora", "Nombre_Partida", "Data", "Juego", "Jugador") FROM stdin;
\.


--
-- Name: SavedGames_ID_SavedGame_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('"SavedGames_ID_SavedGame_seq"', 1, false);


--
-- Name: HighScore_PK; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "HighScores"
    ADD CONSTRAINT "HighScore_PK" PRIMARY KEY ("ID_HS");


--
-- Name: Juego_PK; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Juegos"
    ADD CONSTRAINT "Juego_PK" PRIMARY KEY ("ID_Juego");


--
-- Name: Jugador_PK; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Jugadores"
    ADD CONSTRAINT "Jugador_PK" PRIMARY KEY ("ID_Jugador");


--
-- Name: NombreJugador_Unique; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Jugadores"
    ADD CONSTRAINT "NombreJugador_Unique" UNIQUE ("Username");


--
-- Name: Nombre_Unique; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "Juegos"
    ADD CONSTRAINT "Nombre_Unique" UNIQUE ("Nombre_Juego");


--
-- Name: Registro_PK; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "RegistroDeUso"
    ADD CONSTRAINT "Registro_PK" PRIMARY KEY ("ID_Registro");


--
-- Name: SavedGame_PK; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "SavedGames"
    ADD CONSTRAINT "SavedGame_PK" PRIMARY KEY ("ID_SavedGame");


--
-- Name: fki_Juego_FK; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX "fki_Juego_FK" ON "SavedGames" USING btree ("Juego");


--
-- Name: fki_Juego_HS_FK; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX "fki_Juego_HS_FK" ON "HighScores" USING btree ("Juego");


--
-- Name: fki_Juego_Reg_FK; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX "fki_Juego_Reg_FK" ON "RegistroDeUso" USING btree ("Juego");


--
-- Name: fki_Jugador_FK; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX "fki_Jugador_FK" ON "SavedGames" USING btree ("Jugador");


--
-- Name: fki_Jugador_HS_FK; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX "fki_Jugador_HS_FK" ON "HighScores" USING btree ("Jugador");


--
-- Name: fki_Jugador_Reg_FK; Type: INDEX; Schema: public; Owner: postgres
--

CREATE INDEX "fki_Jugador_Reg_FK" ON "RegistroDeUso" USING btree ("Jugador");


--
-- Name: Juego_HS_FK; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "HighScores"
    ADD CONSTRAINT "Juego_HS_FK" FOREIGN KEY ("Juego") REFERENCES "Juegos"("ID_Juego");


--
-- Name: Juego_Reg_FK; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "RegistroDeUso"
    ADD CONSTRAINT "Juego_Reg_FK" FOREIGN KEY ("Juego") REFERENCES "Juegos"("ID_Juego");


--
-- Name: Juego_SG_FK; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "SavedGames"
    ADD CONSTRAINT "Juego_SG_FK" FOREIGN KEY ("Juego") REFERENCES "Juegos"("ID_Juego");


--
-- Name: Jugador_HS_FK; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "HighScores"
    ADD CONSTRAINT "Jugador_HS_FK" FOREIGN KEY ("Jugador") REFERENCES "Jugadores"("ID_Jugador");


--
-- Name: Jugador_Reg_FK; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "RegistroDeUso"
    ADD CONSTRAINT "Jugador_Reg_FK" FOREIGN KEY ("Jugador") REFERENCES "Jugadores"("ID_Jugador");


--
-- Name: Jugador_SG_FK; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY "SavedGames"
    ADD CONSTRAINT "Jugador_SG_FK" FOREIGN KEY ("Jugador") REFERENCES "Jugadores"("ID_Jugador");


--
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


--
-- PostgreSQL database dump complete
--

