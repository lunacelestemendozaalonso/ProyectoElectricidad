CREATE DATABASE electricidad;
USE electricidad;
-----------------------------------------------------------------------------

-- Tabla PRODUCTOR
CREATE TABLE productor (
    id_productor INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100),
    produccion_media DECIMAL(10,2),
    produccion_maxima DECIMAL(10,2),
    fecha_entrada DATE
);

-- Subtipos de PRODUCTOR
CREATE TABLE presa (
    id_productor INT PRIMARY KEY,
    capacidad_maxima INT,
    ocupacion VARCHAR(100),
    num_turbinas INT,
    FOREIGN KEY (id_productor) REFERENCES productor(id_productor)
);

CREATE TABLE solar (
    id_productor INT PRIMARY KEY,
    total_paneles INT,
    horas_sol DECIMAL(5,2),
    tipo ENUM('fotovoltaica','termodinámica'),
    FOREIGN KEY (id_productor) REFERENCES productor(id_productor)
);

CREATE TABLE nuclear (
    id_productor INT PRIMARY KEY,
    num_reactores INT,
    residuos_nucleares DECIMAL(10,2),
    vol_plutonio DECIMAL(10,2),
    FOREIGN KEY (id_productor) REFERENCES productor(id_productor)
);

CREATE TABLE termica (
    id_productor INT PRIMARY KEY,
    num_hornos INT,
    vol_carbon DECIMAL(10,2),
    vol_emisiongases DECIMAL(10,2),
    FOREIGN KEY (id_productor) REFERENCES productor(id_productor)
);

-- SUMINISTRADOR y TRANSPORTISTA
CREATE TABLE suministrador (
    id_suministrador INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100),
    pais VARCHAR(100)
);

CREATE TABLE transportista (
    id_transportista INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100),
    matricula VARCHAR(50),
    direccion VARCHAR(100)
);

-- COMPRA (N:M)
CREATE TABLE compra (
    id_compra INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    id_productor INT,
    id_suministrador INT,
    id_transportista INT,
    cantidad DECIMAL(10,2),
    fecha DATE,
    FOREIGN KEY (id_productor) REFERENCES nuclear(id_productor),
    FOREIGN KEY (id_suministrador) REFERENCES suministrador(id_suministrador),
    FOREIGN KEY (id_transportista) REFERENCES transportista(id_transportista)
);

-- ESTACIÓN PRIMARIA
CREATE TABLE est_primaria (
    id_primaria INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100),
    transformadores INT
);

-- ENTREGA (N:M)
CREATE TABLE entrega (
    id_entrega INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    id_productor INT,
    id_primaria INT,
    cantidad DECIMAL(10,2),
    fecha DATE,
    FOREIGN KEY (id_productor) REFERENCES productor(id_productor),
    FOREIGN KEY (id_primaria) REFERENCES est_primaria(id_primaria)
);

-- RED
CREATE TABLE red (
    id_red INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    id_primaria INT,
    FOREIGN KEY (id_primaria) REFERENCES est_primaria(id_primaria)
);

-- COMPAÑÍA
CREATE TABLE compania (
    id_compañia INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    nombre VARCHAR(100)
);

-- PERTENECE
CREATE TABLE pertenece (
    id_pertenece INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    id_red INT,
    id_compañia INT,
    FOREIGN KEY (id_red) REFERENCES red(id_red),
    FOREIGN KEY (id_compañia) REFERENCES compania(id_compañia)
);

-- ENVIA_ENERGIA
CREATE TABLE envia_energia (
    id_envio INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    id_red_origen INT,
    id_red_destino INT,
    volumen DECIMAL(10,2),
    FOREIGN KEY (id_red_origen) REFERENCES red(id_red),
    FOREIGN KEY (id_red_destino) REFERENCES red(id_red)
);

-- LINEA
CREATE TABLE linea (
    id_linea INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    longitud DECIMAL(10,2),
    id_red INT,
    FOREIGN KEY (id_red) REFERENCES red(id_red)
);

-- SUBESTACION
CREATE TABLE subestacion (
    id_subestacion INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    id_linea INT,
    FOREIGN KEY (id_linea) REFERENCES linea(id_linea)
);

-- PROVINCIA
CREATE TABLE provincia (
    id_provincia INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    codigo VARCHAR(20),
    nombre VARCHAR(100)
);

-- ZONA
CREATE TABLE zona (
    id_zona INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    consumo_medio DECIMAL(10,2),
    particulares INT,
    empresas INT,
    instituciones INT,
    id_provincia INT,
    FOREIGN KEY (id_provincia) REFERENCES provincia(id_provincia)
);

-- DISTRIBUYE
CREATE TABLE distribuye (
    id_distribuye INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
    id_subestacion INT,
    id_zona INT,
    FOREIGN KEY (id_subestacion) REFERENCES subestacion(id_subestacion),
    FOREIGN KEY (id_zona) REFERENCES zona(id_zona)
);