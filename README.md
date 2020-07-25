<html>

<head>
    <meta content="text/html; charset=UTF-8" http-equiv="content-type">
</head>

<h1>Sistemas Operativos - Delibird</h1>

<body class="c52 c117">
    <hr style="page-break-before:always;display:none;">
    <p class="c69 c17 c24"><span class="c67 c40 c48 c106"></span></p>
    <p class="c69 c17"><span class="c27 c40 c68">&Iacute;ndice</span></p>
    <p class="c17 c29"><span class="c3"><a class="c19" href="#h.gjdgxs">Versi&oacute;n de Cambios</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.gjdgxs">2</a></span></p>
    <p class="c50 c17"><span class="c3"><a class="c19" href="#h.6qd0js6b0z7o">Objetivos y Normas de
                resoluci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.6qd0js6b0z7o">6</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.3znysh7">Objetivos del Trabajo
                Pr&aacute;ctico</a></span><span class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c3"><a class="c19" href="#h.3znysh7">6</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.2et92p0">Caracter&iacute;sticas</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2et92p0">6</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.tyjcwt">Evaluaci&oacute;n del Trabajo
                Pr&aacute;ctico</a></span><span class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c3"><a class="c19" href="#h.tyjcwt">6</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.3dy6vkm">Deployment y Testing del Trabajo
                Pr&aacute;ctico</a></span><span class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c3"><a class="c19" href="#h.3dy6vkm">7</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.1t3h5sf">Aclaraciones</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1t3h5sf">7</a></span></p>
    <p class="c50 c17"><span class="c3"><a class="c19" href="#h.2s8eyo1">Abstract</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.2s8eyo1">8</a></span></p>
    <p class="c17 c50"><span class="c3"><a class="c19" href="#h.17dp8vu">Arquitectura del Sistema</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.17dp8vu">9</a></span></p>
    <p class="c50 c17"><span class="c22"><a class="c19" href="#h.3rdcrjn">Proceso Broker</a></span><span
            class="c22">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.3rdcrjn">10</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.26in1rg">Abstract - Message Queue (MQ)</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.26in1rg">10</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.lnxbz9">Lineamiento e Implementaci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.lnxbz9">11</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.35nkun2">Administraci&oacute;n de mensajes</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.35nkun2">11</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1ksv4uv">Particiones din&aacute;micas con
                compactaci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1ksv4uv">12</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.44sinio">Procedimiento para almacenamiento de
                datos</a></span><span class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c3"><a class="c19" href="#h.44sinio">12</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.2jxsxqh">Algoritmos para elecci&oacute;n de
                partici&oacute;n libre y elecci&oacute;n de v&iacute;ctima</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2jxsxqh">12</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.z337ya">Buddy System</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.z337ya">13</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3j2qqm3">Dump de la Cach&eacute;</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3j2qqm3">13</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1y810tw">Tipos de Suscribers</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1y810tw">14</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.4i7ojhp">Suscriptor global</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.4i7ojhp">14</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.2xcytpi">Suscriptor globales por mensajes
                correlativos</a></span><span class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c3"><a class="c19" href="#h.2xcytpi">14</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1ci93xb">Listado de Message Queues</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1ci93xb">15</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3whwml4">Tipos de datos</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3whwml4">15</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.2bn6wsx">Logs obligatorios</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2bn6wsx">15</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.qsh70q">Archivo de Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.qsh70q">16</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3as4poj">Ejemplo de Archivo de
                Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3as4poj">16</a></span></p>
    <p class="c50 c17"><span class="c22"><a class="c19" href="#h.1pxezwc">Proceso Game Card</a></span><span
            class="c22">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.1pxezwc">17</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.49x2ik5">Tall Grass</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.49x2ik5">17</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.2p2csry">Metadata</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2p2csry">17</a></span></p>
    <p class="c17 c39"><span class="c3"><a class="c19" href="#h.147n2zr">Bitmap</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.147n2zr">18</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.3o7alnk">Files Metadata</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3o7alnk">18</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.23ckvvd">Datos</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.23ckvvd">18</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.ihv636">Lineamiento e Implementaci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.ihv636">19</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.32hioqz">Archivos Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.32hioqz">19</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1hmsyys">New Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1hmsyys">20</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.41mghml">Catch Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.41mghml">20</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.2grqrue">Get Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2grqrue">21</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.vx1227">Archivo de Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.vx1227">22</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3fwokq0">Ejemplo de Archivo de
                Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3fwokq0">22</a></span></p>
    <p class="c50 c17"><span class="c22"><a class="c19" href="#h.1v1yuxt">Proceso Team</a></span><span
            class="c22">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.1v1yuxt">23</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.4f1mdlm">Lineamiento e Implementaci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.4f1mdlm">23</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.2u6wntf">Planificaci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2u6wntf">23</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.19c6y18">Diagrama de estados de un Entrenador</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.19c6y18">24</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3tbugp1">Competici&oacute;n y Deadlock</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3tbugp1">25</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.28h4qwu">Tipo de mensajes</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.28h4qwu">25</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.nmf14n">Appeared Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.nmf14n">25</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.37m2jsg">Get Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.37m2jsg">26</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.1mrcu09">Catch Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1mrcu09">26</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.46r0co2">Localized Pok&eacute;mon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.46r0co2">26</a></span></p>
    <p class="c39 c17"><span class="c3"><a class="c19" href="#h.2lwamvv">Caught Pok&eacute;mon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2lwamvv">27</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.111kx3o">Logs obligatorios</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.111kx3o">27</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.3l18frh">Archivo de Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3l18frh">28</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.206ipza">Ejemplo de Archivo de
                Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.206ipza">28</a></span></p>
    <p class="c50 c17"><span class="c22"><a class="c19" href="#h.4k668n3">Proceso Game Boy</a></span><span
            class="c22">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.4k668n3">30</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.2zbgiuw">Lineamiento e Implementaci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2zbgiuw">30</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1egqt2p">Broker - New Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1egqt2p">30</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3ygebqi">Broker - Appeared Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3ygebqi">30</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.2dlolyb">Broker - Catch Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2dlolyb">31</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.sqyw64">Broker - Caught Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.sqyw64">31</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3cqmetx">Broker - Get Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3cqmetx">31</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1rvwp1q">Team - Appeared Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1rvwp1q">31</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.4bvk7pj">Game Card - New Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.4bvk7pj">31</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.2r0uhxc">Game Card - Catch Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2r0uhxc">31</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1664s55">Game Card - Get Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1664s55">31</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3q5sasy">Modo Suscriptor</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3q5sasy">31</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.25b2l0r">Logs obligatorios</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.25b2l0r">32</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.kgcv8k">Archivo de Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.kgcv8k">32</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.34g0dwd">Ejemplo de Archivo de
                Configuraci&oacute;n</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.34g0dwd">32</a></span></p>
    <p class="c50 c17"><span class="c22"><a class="c19" href="#h.1jlao46">Anexo I - Ejemplos de Flujos</a></span><span
            class="c22">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.1jlao46">33</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.43ky6rz">Flujo New Pokemon - Appeared Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.43ky6rz">33</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.2iq8gzs">Flujo Get Pokemon - Localized
                Pokemon</a></span><span class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c3"><a class="c19" href="#h.2iq8gzs">33</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.xvir7l">Flujo Catch Pokemon - Caught Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.xvir7l">34</a></span></p>
    <p class="c50 c17"><span class="c22"><a class="c19" href="#h.3hv69ve">Anexo II - Mensajes en memoria</a></span><span
            class="c22">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c22"><a class="c19"
                href="#h.3hv69ve">35</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1x0gk37">Tama&ntilde;o de New Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1x0gk37">35</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.4h042r0">Tama&ntilde;o de Get Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.4h042r0">35</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.2w5ecyt">Tama&ntilde;o de Appeared Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2w5ecyt">35</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.1baon6m">Tama&ntilde;o de Catch Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1baon6m">36</a></span></p>
    <p class="c0"><span class="c3"><a class="c19" href="#h.3vac5uf">Tama&ntilde;o de Caught Pokemon</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.3vac5uf">36</a></span></p>
    <p class="c50 c17"><span class="c22"><a class="c19" href="#h.pkwqa1">Descripci&oacute;n de las
                entregas</a></span><span class="c22">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c22"><a class="c19" href="#h.pkwqa1">37</a></span></p>
    <p class="c1"><span class="c33"><a class="c19" href="#h.9vyywhatg0r2">Hito 1: Conexi&oacute;n
                Inicial</a></span><span class="c33">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c33"><a class="c19" href="#h.9vyywhatg0r2">37</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.1opuj5n">Hito 2: Avance del Grupo</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1opuj5n">37</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.1302m92">Hito 3: Checkpoint &ldquo;Presencial&rdquo; -
                V&iacute;a pantalla compartida</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.1302m92">38</a></span></p>
    <p class="c1"><span class="c3"><a class="c19" href="#h.2250f4o">Hito 4: Avance del Grupo</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.2250f4o">38</a></span></p>
    <p class="c17 c116"><span class="c3"><a class="c19" href="#h.haapch">Hito 5: Entregas Finales</a></span><span
            class="c3">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span class="c3"><a class="c19"
                href="#h.haapch">38</a></span></p>
    <h1 class="c20 c17" id="h.6qd0js6b0z7o"><span class="c67 c27 c40 c48">Objetivos y Normas de resoluci&oacute;n</span>
    </h1>
    <h2 class="c16" id="h.3znysh7"><span class="c31">Objetivos del Trabajo Pr&aacute;ctico</span></h2>
    <p class="c2"><span class="c3">Mediante la realizaci&oacute;n de este trabajo se espera que el alumno:</span></p>
    <ul class="c32 lst-kix_list_2-0 start">
        <li class="c23"><span class="c3">Adquiera conceptos pr&aacute;cticos del uso de las distintas herramientas de
                programaci&oacute;n e interfaces (APIs) que brindan los sistemas operativos.</span></li>
        <li class="c23"><span class="c3">Entienda aspectos del dise&ntilde;o de un sistema operativo.</span></li>
        <li class="c23"><span class="c3">Afirme diversos conceptos te&oacute;ricos de la materia mediante la
                implementaci&oacute;n pr&aacute;ctica de algunos de ellos.</span></li>
        <li class="c23"><span class="c3">Se familiarice con t&eacute;cnicas de programaci&oacute;n de sistemas, como el
                empleo de makefiles, archivos de configuraci&oacute;n y archivos de log.</span></li>
        <li class="c69 c47"><span class="c3">Conozca con grado de detalle la operatoria de Linux mediante la
                utilizaci&oacute;n de un lenguaje de programaci&oacute;n de relativamente bajo nivel como C.</span></li>
    </ul>
    <h2 class="c16" id="h.2et92p0"><span class="c31">Caracter&iacute;sticas</span></h2>
    <ul class="c32 lst-kix_list_19-0 start">
        <li class="c23"><span>Modalidad: grupal (5 integrantes +- 0) y obligatorio</span></li>
        <li class="c23"><span>Tiempo estimado para su desarrollo: 90 d&iacute;as</span></li>
        <li class="c23"><span>Fecha de comienzo: &nbsp;</span><span>03 de Abril</span></li>
        <li class="c23"><span>Fecha de primera entrega: 25 de Julio </span><span class="c4 c30">(fecha tentativa a la
                espera de actualizaci&oacute;n de calendario acad&eacute;mico)</span></li>
        <li class="c23"><span>Fecha de segunda entrega: 1 de Agosto </span><span class="c4 c30">(fecha tentativa a la
                espera de actualizaci&oacute;n de calendario acad&eacute;mico)</span></li>
        <li class="c23"><span>Fecha de tercera entrega: 22 de Agosto </span><span class="c4 c30">(fecha tentativa a la
                espera de actualizaci&oacute;n de calendario acad&eacute;mico)</span></li>
        <li class="c69 c47"><span>Lugar de correcci&oacute;n: Laboratorio de Medrano</span></li>
    </ul>
    <h2 class="c16" id="h.tyjcwt"><span class="c31">Evaluaci&oacute;n del Trabajo Pr&aacute;ctico</span></h2>
    <p class="c75"><span class="c3">El trabajo pr&aacute;ctico consta de una evaluaci&oacute;n en 2 etapas. </span></p>
    <p class="c75"><span>La primera etapa consistir&aacute; en las pruebas de los programas desarrollados en el
            laboratorio. Las pruebas del trabajo pr&aacute;ctico se subir&aacute;n oportunamente y con suficiente tiempo
            para que los alumnos puedan evaluarlas con antelaci&oacute;n. Queda aclarado que para que un trabajo
            pr&aacute;ctico sea considerado </span><span class="c45">evaluable</span><span class="c3">, el mismo debe
            proporcionar registros de su &nbsp;funcionamiento de la forma m&aacute;s clara posible.</span></p>
    <p class="c75"><span>La segunda etapa se dar&aacute; en caso de </span><span
            class="c45">aprobada</span><span>&nbsp;la primera y constar&aacute; de un coloquio, con el objetivo de
            afianzar los conocimientos adquiridos durante el desarrollo del trabajo pr&aacute;ctico y terminar de
            definir la nota de cada uno de los integrantes del grupo, por lo que se </span><span
            class="c45">recomienda</span><span class="c3">&nbsp;que la carga de trabajo se distribuya de la manera
            m&aacute;s equitativa posible.</span></p>
    <p class="c75"><span class="c3">Cabe aclarar que el trabajo equitativo no asegura la aprobaci&oacute;n de la
            totalidad de los integrantes, sino que cada uno tendr&aacute; que defender y explicar tanto te&oacute;rica
            como pr&aacute;cticamente lo desarrollado y aprendido a lo largo de la cursada.</span></p>
    <p class="c75"><span>La defensa del trabajo pr&aacute;ctico (o coloquio) consta de la relaci&oacute;n de lo visto
            durante la teor&iacute;a con lo implementado. De esta manera, </span><span>una implementaci&oacute;n que
            contradiga a lo visto en clase o lo escrito en el documento </span><span class="c4">es motivo de
            desaprobaci&oacute;n del trabajo pr&aacute;ctico</span><span>.</span></p>
    <h2 class="c16" id="h.3dy6vkm"><span class="c31">Deployment y Testing del Trabajo Pr&aacute;ctico</span></h2>
    <p class="c2"><span>Al tratarse de una plataforma distribuida, los procesos involucrados podr&aacute;n ser
            ejecutados en diversas computadoras. La cantidad de computadoras involucradas y la distribuci&oacute;n de
            los diversos procesos en estas ser&aacute; definida en cada uno de los tests de la evaluaci&oacute;n y
        </span><span class="c40">es posible cambiar la misma en el momento de la evaluaci&oacute;n</span><span
            class="c3">. Es responsabilidad del grupo automatizar el despliegue de los diversos procesos con sus
            correspondientes archivos de configuraci&oacute;n para cada uno de los diversos tests a evaluar.</span></p>
    <p class="c2"><span class="c3">Todo esto estar&aacute; detallado en el documento de pruebas que se publicar&aacute;
            cercano a la fecha de Entrega Final. Archivos y programas de ejemplo se pueden encontrar en el repositorio
            de la c&aacute;tedra. </span></p>
    <p class="c2"><span class="c40">Finalmente, recordar la existencia de las </span><span class="c45 c49 c40"><a
                class="c19"
                href="https://www.google.com/url?q=https://faq.utnso.com.ar/ntp&amp;sa=D&amp;ust=1595200539629000&amp;usg=AOvVaw2i9Bt6InYzuCoQZXen-4Wq">Normas
                del Trabajo Pr&aacute;ctico</a></span><span class="c40">&nbsp;donde se especifican todos los
            lineamientos de c&oacute;mo se desarrollar&aacute; la materia durante el cuatrimestre.</span></p>
    <p class="c2 c24"><span class="c3"></span></p>
    <h2 class="c16" id="h.1t3h5sf"><span class="c31">Aclaraciones</span></h2>
    <p class="c2"><span>Debido al fin acad&eacute;mico del trabajo pr&aacute;ctico, los conceptos reflejados son, en
            general, </span><span class="c45">versiones simplificadas o alteradas</span><span class="c3">&nbsp;de los
            componentes reales de hardware y de sistemas operativos modernos, a fin de resaltar aspectos de
            dise&ntilde;o.</span></p>
    <p class="c2"><span class="c3">Invitamos a los alumnos a leer las notas y comentarios al respecto que haya en el
            enunciado, reflexionar y discutir con sus compa&ntilde;eros, ayudantes y docentes al respecto.</span></p>
    <h1 class="c20 c17 c96" id="h.4d34og8"><span class="c67 c27 c40 c48"></span></h1>
    <hr style="page-break-before:always;display:none;">
    <p class="c2 c24"><span class="c3"></span></p>
    <h1 class="c20 c17" id="h.2s8eyo1"><span class="c67 c27 c40 c48">Abstract</span></h1>
    <p class="c2"><span class="c3">El objetivo del trabajo pr&aacute;ctico consiste en desarrollar una soluci&oacute;n
            que permita la simulaci&oacute;n de un sistema distribuido que utiliza el concepto de Colas de Mensajes (o
            Message Queue).</span></p>
    <p class="c50"><span class="c3">Los componentes incluidos dentro de la arquitectura del sistema deber&aacute;n
            trabajar en conjunto para la planificaci&oacute;n y ejecuci&oacute;n de distintas operaciones, entre las que
            se encuentran, por ejemplo: leer y escribir valores. Las operaciones que conforman estos mensajes
            est&aacute;n asociadas y vinculadas al mundo de Pok&eacute;mon.</span></p>
    <p class="c2"><span>Message Queue (a partir de ahora MQ) es una t&eacute;cnica de software utilizada para la
            comunicaci&oacute;n entre procesos (IPC) basada en el concepto de Colas (Queue). En ella, distintos procesos
            dejan mensajes y otros los leen de manera asincr&oacute;nica. De esta manera, se permite el desarrollo de un
            sistema completamente distribuido, escalable e independiente</span><span class="c3">.</span></p>
    <p class="c2"><span class="c3">Los componentes del sistema ser&aacute;n:</span></p>
    <ul class="c32 lst-kix_list_7-0 start">
        <li class="c25 c17"><span>Un proceso publisher que ingrese mensajes al sistema (Game Boy).</span></li>
        <li class="c25 c17"><span>Un proceso administrador de las Colas de Mensajes (Broker).</span></li>
        <li class="c25 c17"><span>Procesos que obtengan los mensajes y planifiquen en funci&oacute;n de ellos
                (Team).</span></li>
        <li class="c2 c47"><span>Procesos filesystem que se encarguen de mantener los archivos en el tiempo (Game
                Card).</span></li>
    </ul>
    <p class="c2 c24"><span class="c3"></span></p>
    <hr style="page-break-before:always;display:none;">
    <p class="c50 c24"><span class="c3"></span></p>
    <h1 class="c20 c17" id="h.17dp8vu"><span class="c67 c27 c40 c48">Arquitectura del Sistema </span></h1>
    <p class="c26"><span class="c3">Como dijimos anteriormente el sistema consta de 4 m&oacute;dulos independientes los
            cuales interact&uacute;an entre s&iacute; como se muestra en el siguiente diagrama.</span></p>
    <p class="c26 c24"><span class="c3"></span></p>
    <p class="c42"><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 416.50px; height: 241.56px;"><img
                alt="" src="images/image2.png"
                style="width: 416.50px; height: 241.56px; margin-left: 0.00px; margin-top: 0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></p>
    <p class="c26"><span class="c3">El Game Boy ser&aacute; nuestro punto de partida y asimismo, que conocer&aacute; y
            permitir&aacute; el env&iacute;o de mensajes a distintos m&oacute;dulos de nuestro sistema.</span></p>
    <p class="c26"><span class="c3">El proceso Broker ser&aacute; el encargado de administrar las distintas Colas de
            Mensajes existentes en el sistema. Para esto, el mismo mantendr&aacute; distintas caracter&iacute;sticas y
            funcionalidades propias de un sistema de Cola de Mensajes real, encarg&aacute;ndose de mantener, entender y
            distribuir los distintos mensajes.</span></p>
    <p class="c26"><span>El proceso Team contendr&aacute; una lista de entrenadores con distintos objetivos de captura
            de Pokemons. </span><span>Nuestro proceso deber&aacute; planificar a los entrenadores correctamente para que
            cumplan sus objetivos cooperativamente dentro de un mapa</span><span class="c3">. De esta manera, los
            Pokemon seran recursos que los distintos entrenadores deber&aacute;n atrapar movi&eacute;ndose por el mapa
            (apropiarse) y luego intercambiar en caso de ser necesario (se produzca un deadlock).</span></p>
    <p class="c26"><span>Por &uacute;ltimo, nuestro proceso Game Card ser&aacute; el encargado de conocer qu&eacute;
            Pokemon se encuentran disponibles dentro del mapa y en qu&eacute; posici&oacute;n est&aacute; cada uno.
            Deber&aacute; mantener distintos permisos y atribuciones para que solo un proceso pueda acceder al mismo
            tiempo a &eacute;l. Al estar este proceso conectado al Broker y asociarse a una cola de mensajes
            espec&iacute;fica nos permite generar redundancia de Game Card y poder replicar con distintas demoras o
            distintos file system los mismos archivos.</span>
        <hr style="page-break-before:always;display:none;">
    </p>
    <h1 class="c20 c17" id="h.3rdcrjn"><span class="c67 c27 c40 c48">Proceso Broker</span></h1>
    <p class="c2"><span class="c3">Ser&aacute; el encargado de administrar las colas de mensajes de nuestro sistema.
            Como tal tendr&aacute; la responsabilidad de:</span></p>
    <ol class="c32 lst-kix_list_14-0 start" start="1">
        <li class="c25 c17"><span>Administrar los suscriptores (Teams, Game Cards) asociados a las distintas
                colas.</span></li>
        <li class="c25 c17"><span>Administrar la recepci&oacute;n, env&iacute;o y confirmaci&oacute;n de todos los
                mensajes a los m&uacute;ltiples suscriptores.</span></li>
        <li class="c25 c17"><span>Mantener un registro de los &uacute;ltimos mensajes recibidos de las colas indicadas
                para futuros suscriptores.</span></li>
        <li class="c2 c47"><span>Mantener e informar en todo momento los estados de las colas, con sus mensajes y
                suscriptores.</span></li>
    </ol>
    <p class="c2"><span class="c3">Para explicar esto, primero nos enfocaremos en el conceptos t&eacute;cnicos de
            qu&eacute; es una Cola de mensajes (o Message Queue) para luego abordar los aspectos y lineamientos
            t&eacute;cnicos que tendr&aacute; nuestra implementaci&oacute;n. </span></p>
    <h2 class="c16" id="h.26in1rg"><span>Abstract - Message Queue (MQ)</span></h2>
    <p class="c2"><span class="c3">Las colas de mensajes son software que permiten la comunicaci&oacute;n entre procesos
            (IPC) de manera as&iacute;ncrona, lo que significa que el emisor y el receptor del mensaje no necesitan
            interactuar con la cola de mensajes al mismo tiempo. </span></p>
    <p class="c2"><span class="c3">Cada mensaje colocado en una cola se almacena hasta que el/los destinatarios los
            recuperen y/o lean. Las colas de mensajes tienen l&iacute;mites impl&iacute;citos o expl&iacute;citos sobre
            el tama&ntilde;o de los datos que pueden ser transmitidos en un solo mensaje y el n&uacute;mero de mensajes
            que pueden quedar pendientes en la cola.</span></p>
    <p class="c2"><span>De esta manera, vamos a tener varios procesos que van a funcionar como publicadores (o
            Publishers) que van a ser los encargados de dejar mensajes en una Cola de mensajes en particular mientras
            que otros procesos van a funcionar como suscriptores (o </span><span>Suscribers</span><span class="c3">) que
            van a recibir aquellos mensajes que lleguen a las colas de mensajes donde est&eacute;n suscriptos.</span>
    </p>
    <p class="c2"><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 603.51px; height: 90.67px;"><img
                alt="" src="images/image9.png"
                style="width: 603.51px; height: 90.67px; margin-left: -0.00px; margin-top: -0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></p>
    <p class="c2"><span class="c3">En el &aacute;mbito de nuestro trabajo practico implementaremos una serie de colas de
            mensajes que utilizaremos para distintos prop&oacute;sitos que explicaremos m&aacute;s adelante. Dichas
            colas de mensajes deben cumplir con los siguientes aspectos t&eacute;cnicos:</span></p>
    <ol class="c32 lst-kix_list_9-0 start" start="1">
        <li class="c17 c25"><span>Durabilidad: Todo mensaje debe permanecer en la cola de mensajes hasta que todos los
            </span><span>Suscribers</span><span>&nbsp;lo reciban.</span></li>
        <li class="c25 c17"><span>Notificaci&oacute;n de recepci&oacute;n: Todo mensaje entregado debe ser confirmado
                por cada Suscriptor para marcarlo y no enviarse nuevamente al mismo.</span></li>
        <li class="c25 c17"><span>Mantenibilidad: Cada cola de mensaje debe mantener su estado y borrar los mensajes que
                fueron eliminados de la cach&eacute; por el algoritmo de reemplazo</span></li>
        <li class="c2 c47"><span>Asincronismo: La recepci&oacute;n y notificaci&oacute;n de mensajes pueden diferir en
                el tiempo. No deben notificarse inmediatamente a los componentes suscritos a dicha cola.</span></li>
    </ol>
    <h2 class="c16" id="h.lnxbz9"><span class="c31">Lineamiento e Implementaci&oacute;n</span></h2>
    <p class="c2"><span class="c3">El Broker se encarga, como dijimos anteriormente, de la administraci&oacute;n de MQ
            de nuestro sistema, simulando algunos aspectos t&eacute;cnicos de sus implementaciones en la realidad. Por
            otra parte, se incorporan conceptos de la materia como administraci&oacute;n de memoria, mensajer&iacute;a y
            sincronizaci&oacute;n. </span></p>
    <p class="c2"><span class="c3">La funcionalidad principal del Broker es la de administrar las distintas colas de
            mensajes con sus distintos suscriptores. Para esto, esperar&aacute; las solicitudes de los distintos
            m&oacute;dulos para asociarse a las distintas colas que &eacute;l mismo administra. De esta manera, cada uno
            de los clientes/m&oacute;dulos se deber&aacute; comunicar con &eacute;l indicando cual es la cola a la que
            se desea suscribir (en este punto llamaremos al otro m&oacute;dulo como suscriptor). </span></p>
    <p class="c2"><span class="c3">Una vez informado esto, el Broker dispondr&aacute; de una lista de suscriptores por
            cada cola que el mismo administre. En otra instancia de tiempo, un mensaje llegar&aacute; con el destino a
            dicha cola de mensajes y el Broker distribuir&aacute; dicho mensaje a los suscriptores (enviar&aacute; dicho
            mensaje a cada uno de los suscriptores). Al realizar esto se deber&aacute; tener en cuenta lo
            siguiente:</span></p>
    <ol class="c32 lst-kix_list_33-0 start" start="1">
        <li class="c25 c17"><span>Todo mensaje debe ser cacheado dentro de la memoria interna del Broker.</span></li>
        <li class="c25 c17"><span>Todo mensaje debe saber a cuales suscriptores fue enviado y si el mismo fue recibido
                (confirmaci&oacute;n, ACK &oacute; </span><span class="c111">acknowledgement</span><span>).</span></li>
        <li class="c2 c47"><span>Todo mensaje debe tener un identificador un&iacute;voco generado por el Broker que debe
                ser informado al m&oacute;dulo que gener&oacute; el mismo.</span></li>
    </ol>
    <p class="c2"><span>Esta funcionalidad deber&aacute; </span><span class="c4">ser implementada por medio de
            multi-hilos</span><span>. Esta arquitectura permitir&aacute; al Broker poder enviar y transaccionar mensajes
            en simult&aacute;neo a los distintos suscriptores. </span><span class="c22">Cualquier otra
            implementaci&oacute;n que no est&eacute; bajo este concepto ser&aacute; motivo de desaprobaci&oacute;n del
            trabajo pr&aacute;ctico. </span></p>
    <h3 class="c38 c17" id="h.35nkun2"><span class="c5">Administraci&oacute;n de mensajes</span></h3>
    <p class="c2"><span>Como dijimos anteriormente, el Broker mantendr&aacute; una memoria interna en la cual se cachean
            los &uacute;ltimos mensajes recibidos de las distintas colas de mensajes. </span><span>En el mismo
            deber&aacute; registrar</span><span class="c3">:</span></p>
    <ol class="c32 lst-kix_list_35-0 start" start="1">
        <li class="c25 c17"><span>Identificador &uacute;nico del mensaje dentro del sistema.</span></li>
        <li class="c25 c17"><span>El tipo de mensaje (a que cola de mensajes pertenece).</span></li>
        <li class="c25 c17"><span>Los suscriptores a los cuales ya se envi&oacute; el mensaje.</span></li>
        <li class="c2 c47"><span>Los suscriptores que retornaron el ACK del mismo.</span></li>
    </ol>
    <p class="c2"><span class="c3">Se implementar&aacute;n dos esquemas de Administraci&oacute;n de Memoria: Particiones
            din&aacute;micas con compactaci&oacute;n, y Buddy System (descritos m&aacute;s adelante). Se elegir&aacute;
            por archivo de configuraci&oacute;n cual estar&aacute; activa al iniciar la cach&eacute;. Para ambos, se
            definir&aacute; por par&aacute;metro del Broker el tama&ntilde;o m&iacute;nimo de partici&oacute;n y un
            tama&ntilde;o m&aacute;ximo (que ser&aacute; el de toda la memoria).</span></p>
    <p class="c2"><span>Uno de los requerimientos obligatorios que va a tener el Broker es que una vez inicializado ya
            no se podr&aacute; reservar m&aacute;s memoria din&aacute;mica para guardar los datos. Por lo tanto,
        </span><span class="c4">toda la memoria que vaya a ser necesaria</span><span class="c3">&nbsp;para el
            almacenamiento de los datos deber&aacute; ser pre-reservadas din&aacute;micamente en el inicio. Solo se
            deber&aacute; guardar en la porci&oacute;n de datos el contenido del mensaje dejando el tipo, identificador
            y dem&aacute;s flags del mismo en estructuras auxiliares.</span></p>
    <p class="c2"><span>Cada vez que un proceso se suscriba a una cola de mensajes </span><span
            class="c40">deber&aacute; recibir todos los mensajes cacheados de dicha cola de mensajes</span><span
            class="c3">.</span></p>
    <h3 class="c38 c17" id="h.1ksv4uv"><span>Particiones din&aacute;micas con compactaci&oacute;n</span><sup
            class="c83"><a href="#ftnt1" id="ftnt_ref1">[1]</a></sup></h3>
    <p class="c2"><span class="c3">En este esquema, se reservar&aacute; una porci&oacute;n de memoria por cada valor
            almacenado, del tama&ntilde;o exacto de dicho valor. De esta manera, la cantidad de particiones y su
            tama&ntilde;o es variable. Por ejemplo:</span></p>
    <p class="c89"><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 603.51px; height: 164.59px;"><img
                alt="" src="images/image1.png"
                style="width: 603.51px; height: 164.59px; margin-left: 0.00px; margin-top: 0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></p>
    <p class="c2"><span class="c3">En dicho ejemplo, en el caso de almacenar un nuevo valor de 0,2 Kb en el espacio de
            la primera &nbsp;partici&oacute;n libre, se tendr&iacute;a una nueva &ldquo;partici&oacute;n 4&rdquo; de 0,2
            Kb, y al lado una nueva partici&oacute;n libre de 0,3 Kb.</span></p>
    <h4 class="c11" id="h.44sinio"><span class="c66 c45">Procedimiento para almacenamiento de datos</span></h4>
    <ol class="c32 lst-kix_list_29-0 start" start="1">
        <li class="c25 c17"><span>Se buscar&aacute; una partici&oacute;n libre que tenga suficiente memoria continua
                como para contener el valor. En caso de no encontrarla, se pasar&aacute; al paso siguiente (si
                corresponde</span><sup class="c83"><a href="#ftnt2" id="ftnt_ref2">[2]</a></sup><span>, en caso
                contrario se pasar&aacute; al paso 3 directamente).</span></li>
        <li class="c25 c17"><span>Se compactar&aacute; la memoria y se realizar&aacute; una nueva b&uacute;squeda. En
                caso de no encontrarla, se pasar&aacute; al paso siguiente.</span></li>
        <li class="c2 c47"><span>Se proceder&aacute; a eliminar una partici&oacute;n de datos. Luego</span><span>, si no
                se pudo encontrar una partici&oacute;n con suficiente memoria como para contener el
                valor,</span><span>&nbsp;se volver&aacute; al paso 2 o al 3 seg&uacute;n corresponda.</span></li>
    </ol>
    <h4 class="c11" id="h.2jxsxqh"><span class="c66 c45">Algoritmos para elecci&oacute;n de partici&oacute;n libre y
            elecci&oacute;n de v&iacute;ctima</span></h4>
    <p class="c2"><span class="c3">Para seleccionar una partici&oacute;n libre, se deber&aacute; implementar los
            siguientes pares de algoritmos: </span></p>
    <ul class="c32 lst-kix_list_40-0 start">
        <li class="c2 c47"><span>First Fit (primer ajuste) y Best Fit (mejor ajuste).</span></li>
    </ul>
    <p class="c2"><span class="c3">En el caso de tener que eliminar una partici&oacute;n, los algoritmos a implementar
            ser&aacute;n:</span></p>
    <ul class="c32 lst-kix_list_15-0 start">
        <li class="c2 c47"><span>FIFO (First In First Out) y LRU (Least Recently Used).</span></li>
    </ul>
    <p class="c2"><span class="c3">En ambos casos, el algoritmo a utilizar se definir&aacute; por archivo de
            configuraci&oacute;n.</span></p>
    <h3 class="c38 c17" id="h.z337ya"><span>Buddy System</span><sup class="c83"><a href="#ftnt3"
                id="ftnt_ref3">[3]</a></sup></h3>
    <p class="c2"><span class="c3">En este esquema, se reservar&aacute; una partici&oacute;n de memoria por cada valor
            almacenado, del tama&ntilde;o potencia de 2 que sea m&aacute;s cercano a dicho valor. Por ejemplo:</span>
    </p>
    <p class="c89"><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 603.51px; height: 160.74px;"><img
                alt="" src="images/image4.png"
                style="width: 603.51px; height: 160.74px; margin-left: 0.00px; margin-top: 0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></p>
    <p class="c2"><span class="c3">En dicho ejemplo, en caso de almacenar un nuevo valor de 63 B en el espacio de la
            primer particion libre, generar&iacute;a una nueva &ldquo;partici&oacute;n 3&rdquo; de 64 B, y al lado
            quedar&iacute;a una nueva partici&oacute;n libre de 64 B. </span></p>
    <p class="c2"><span class="c3">El procedimiento de almacenamiento de datos ser&aacute; similar al de las particiones
            din&aacute;micas, con la salvedad que no existir&aacute; la compactaci&oacute;n en el algoritmo Buddy
            System. FIFO y LRU ser&aacute;n los algoritmos a implementar para la elecci&oacute;n de v&iacute;ctima en un
            reemplazo (al igual que en el algoritmo previo, modificable por archivo de configuraci&oacute;n)</span></p>
    <h3 class="c38 c17" id="h.3j2qqm3"><span class="c5">Dump de la Cach&eacute;</span></h3>
    <p class="c2"><span class="c3">Ser&aacute; requerimiento del motor de administraci&oacute;n de memoria que
            &eacute;ste pueda depositar en un archivo el estado actual de la memoria en la cach&eacute; seg&uacute;n el
            esquema seleccionado. Para solicitar dicho dump, se enviar&aacute; una se&ntilde;al SIGUSR1 que
            deber&aacute; ser manejada e inicializada.</span></p>
    <p class="c2"><span>No se pretende ver el contenido de la informaci&oacute;n almacenada, sino las particiones
            asignadas/libres, indicando su direcci&oacute;n de comienzo y fin, su tama&ntilde;o en bytes,
        </span><span>tiempos de LRU,</span><span class="c3">&nbsp;el tipo de cola de mensajes que pertenece y su
            identificador.</span></p>
    <p class="c2"><span class="c45 c33 c48 c102">Ejemplo:</span></p>
    <p class="c2"><span
            class="c3">-----------------------------------------------------------------------------------------------------------------------------<br>Dump:
            14/07/2012 10:11:12<br>Partici&oacute;n 1: 0x000 -
            0x3FF.&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[X]&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Size:
            1024b&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;LRU:&lt;VALOR&gt;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Cola:&lt;COLA&gt;
            &nbsp; ID:&lt;ID&gt;<br>Partici&oacute;n 2: 0x400 - 0x409.
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[L]&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Size:
            9b<br>Partici&oacute;n 3: 0x40A - 0x40B. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[L]
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Size:
            1b<br>-----------------------------------------------------------------------------------------------------------------------------</span>
    </p>
    <h3 class="c17 c38" id="h.1y810tw"><span>Tipos de </span><span>Suscribers</span></h3>
    <p class="c2"><span class="c3">Todo mensaje en una implementaci&oacute;n real tiene dos atributos claves: Su
            identificador y su identificador correlacional (o correlation id). El primero es un identificador
            &uacute;nico que asigna el administrador de colas de mensajes (como ya explicamos anteriormente), mientras
            que el segundo es el identificador correlacional del mensaje al cual est&aacute; asociado. &nbsp;</span></p>
    <p class="c2"><span class="c3">Esto significa que, si se manda el mensaje A en una cola de mensajes
            asign&aacute;ndole el identificador &ldquo;1&rdquo;, quienes est&eacute;n suscritos a esa cola
            recibir&aacute;n dicho mensaje junto con su ID. En caso de que alg&uacute;n suscriptor deba responder este
            mensaje, enviar&aacute; un mensaje B a otra cola de mensajes donde se le asignar&aacute; un nuevo
            identificador (por ejemplo &ldquo;2&rdquo;), pero el emisor asigna en el valor correlacional el
            identificador del mensaje al cual est&aacute; respondiendo (en este caso &ldquo;1&rdquo;).</span></p>
    <p class="c2"><span class="c3">De esta manera un m&oacute;dulo puede enviar un mensaje a una cola, y esperar en otra
            cola de mensajes la respuesta asociada al primero que envi&oacute;. Para esto hay que tener en cuenta varias
            cosas:</span></p>
    <ul class="c32 lst-kix_list_16-0 start">
        <li class="c25 c17"><span>Tiene que existir un protocolo de comunicaci&oacute;n en el cual el proceso que
                env&iacute;a el primer mensaje sabe que tiene que ir a buscar la respuesta a otra cola y el que genere
                la respuesta debe tambi&eacute;n conocer este protocolo.</span></li>
        <li class="c25 c17"><span>El administrador de colas de mensajes debe informar al emisor siempre el identificador
                del mensaje para que este &uacute;ltimo sepa cual es el mensaje correlativo que debe ir a buscar.</span>
        </li>
        <li class="c2 c47"><span class="c3">El administrador de colas de mensajes debe mantener una l&oacute;gica de
                conocer qu&eacute; mensajes con correlativos ya fueron informados en una cola para no generar
                redundancia en la misma. Esto quiere decir que si hay varios suscriptores en la cola de mensajes inicial
                puede haber varias respuestas al mismo (las cuales deber&iacute;an ser la misma respuesta) por lo que es
                el administrador de cola de mensajes el que sabe que ese mensaje ya fue agregado a la cola destino y
                debe ignorarlo.</span></li>
    </ul>
    <p class="c2"><span class="c3">Una vez explicado esto diremos que tendremos dos tipos de suscriptores:</span></p>
    <ol class="c32 lst-kix_list_36-0 start" start="1">
        <li class="c25 c17"><span>Suscriptores globales.</span></li>
        <li class="c2 c47"><span>Suscriptores globales por mensajes correlativos.</span></li>
    </ol>
    <h4 class="c11" id="h.4i7ojhp"><span class="c45 c66">Suscriptor global</span></h4>
    <p class="c2"><span class="c3">Son suscriptores que se asocian globalmente a una cola de mensajes, lo que implica
            que todo mensaje que el Broker rec&iacute;ba a dicha cola de mensajes deber&aacute; ser enviado al
            suscriptor. </span></p>
    <p class="c2"><span class="c3">Cada vez que un proceso se suscriba globalmente a una cola de mensajes, el Broker
            deber&aacute; validar en su memoria principal: si tiene alg&uacute;n mensaje de dicha cola de mensajes y
            enviarles los mismos.</span></p>
    <p class="c2"><span class="c3">Para esto, el Broker manejara una lista de procesos dentro de cada mensaje en memoria
            indicando a qu&eacute; procesos ya fue enviado el mismo. Es responsabilidad del grupo interiorizarse y
            resolver c&oacute;mo se identifica a un proceso espec&iacute;fico frente a una ca&iacute;da y
            recuperaci&oacute;n.</span></p>
    <h4 class="c11" id="h.2xcytpi"><span class="c66 c45">Suscriptor globales por mensajes correlativos</span></h4>
    <p class="c2"><span class="c3">Son suscriptores globales aquellos que se asocian a una cola de mensajes en espera de
            mensajes espec&iacute;ficos con identificadores correlativos que &eacute;l conoce. El Broker env&iacute;a
            todos los mensajes que lleguen a la cola suscrita a este suscriptor y, este &uacute;ltimo verificar&aacute;
            si es un mensaje que &eacute;l requiera (por medio de su identificador correlativo), y de ser as&iacute;
            actuar&aacute; en acci&oacute;n a el. En caso que no sea un mensaje que &eacute;l espera, lo
            ignorar&aacute;.</span></p>
    <h3 class="c38 c17" id="h.1ci93xb"><span class="c5">Listado de Message Queues</span></h3>
    <p class="c2"><span class="c3">El Broker deber&aacute; administrar las siguientes colas de mensajes:</span></p>
    <ul class="c32 lst-kix_list_13-0 start">
        <li class="c25 c17"><span>NEW_POKEMON</span></li>
        <li class="c25 c17"><span>APPEARED_POKEMON</span></li>
        <li class="c25 c17"><span>CATCH_POKEMON</span></li>
        <li class="c25 c17"><span>CAUGHT_POKEMON</span></li>
        <li class="c25 c17"><span class="c3">GET_POKEMON</span></li>
        <li class="c2 c47"><span>LOCALIZED_POKEMON</span></li>
    </ul>
    <h3 class="c38 c17" id="h.3whwml4"><span class="c5">Tipos de datos</span></h3>
    <p class="c2"><span>Dado que el trabajo pr&aacute;ctico mantendr&aacute; seis tipos de mensajes distintos (uno por
            cada cola de mensajes), se </span><span>normalizar&aacute;n</span><span class="c3">&nbsp;los tipos de datos
            a utilizar para que el tama&ntilde;o que ocupe cada uno, dentro de la memoria principal, sea
            homog&eacute;neo a todos los grupos. El objetivo de esto es otorgar una manera r&aacute;pida de
            verificaci&oacute;n y validaci&oacute;n de lo desarrollado por los alumnos.</span></p>
    <p class="c2"><span>Todo dato num&eacute;rico ser&aacute; representado por un </span><span>uint_32</span><span>,
            mientras que todo dato de caracteres din&aacute;micos ser&aacute; representado por: un
        </span><span>uint_32</span><span class="c3">&nbsp;para indicar su tama&ntilde;o, seguido de los caracteres que
            lo componen. Para ejemplificar cada tipo de mensaje les recomendamos leer el Anexo II.</span></p>
    <h2 class="c16" id="h.2bn6wsx"><span class="c31">Logs obligatorios</span></h2>
    <p class="c2"><span>Para permitir la verificaci&oacute;n/validaci&oacute;n del m&oacute;dulo se exigir&aacute; tener
            un archivo de log espec&iacute;fico e independiente que contenga la informaci&oacute;n indicada en esta
            secci&oacute;n. </span><span class="c4">No se permite la inclusi&oacute;n de otros mensajes y
            exclusi&oacute;n de ninguno de los mismos</span><span>&nbsp;(la falta o agregado de alguno puede implicar la
            desaprobaci&oacute;n del grupo). Dado que el log ser&aacute; el medio de validaci&oacute;n del trabajo
            pr&aacute;ctico </span><span class="c4">se exige no utilizar la consola como medio de logueo</span><span
            class="c3">. Cada operaci&oacute;n debe loguearse en una &uacute;nica l&iacute;nea indicando la misma y sus
            datos, en caso que el grupo desee loguear contenido extra deber&aacute; realizarlo en un archivo
            independiente.</span></p>
    <p class="c2"><span class="c3">Las acciones a loguear en este archivo son:</span></p>
    <ol class="c32 lst-kix_list_25-0 start" start="1">
        <li class="c25 c17"><span>Conexi&oacute;n de un proceso al broker.</span></li>
        <li class="c25 c17"><span>Suscripci&oacute;n de un proceso a una cola de mensajes.</span></li>
        <li class="c25 c17"><span>Llegada de un nuevo mensaje a una cola de mensajes.</span></li>
        <li class="c25 c17"><span>Env&iacute;o de un mensaje a un suscriptor espec&iacute;fico.</span></li>
        <li class="c25 c17"><span>Confirmaci&oacute;n de recepci&oacute;n de un suscripci&oacute;n al env&iacute;o de un
                mensaje previo.</span></li>
        <li class="c25 c17"><span>Almacenado de un mensaje dentro de la memoria (indicando posici&oacute;n de inicio de
                su partici&oacute;n).</span></li>
        <li class="c25 c17"><span>Eliminado de una partici&oacute;n de memoria (indicado la posici&oacute;n de inicio de
                la misma).</span></li>
        <li class="c25 c17"><span>Ejecuci&oacute;n de compactaci&oacute;n (para particiones din&aacute;micas) o
                asociaci&oacute;n de bloques (para buddy system). En este &uacute;ltimo, indicar que particiones se
                asociaron (indicar posici&oacute;n inicio de ambas particiones).</span></li>
        <li class="c2 c47"><span>Ejecuci&oacute;n de Dump de cache (solo informar que se solicit&oacute; el
                mismo).</span></li>
    </ol>
    <h2 class="c16" id="h.qsh70q"><span class="c31">Archivo de Configuraci&oacute;n</span></h2>
    <p class="c2 c24"><span class="c3"></span></p><a id="t.ec72c4108a80f36400a17b55d563a3a12d4bb019"></a><a
        id="t.0"></a>
    <table class="c85">
        <tbody>
            <tr class="c10">
                <td class="c57 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Campo</span></p>
                </td>
                <td class="c81 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Tipo</span></p>
                </td>
                <td class="c70 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Descripci&oacute;n</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span>TAMANO_MEMORIA</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Tama&ntilde;o de la memoria en bytes</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span>TAMANO_MINIMO_PARTICION</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Tama&ntilde;o m&iacute;nimo de la partici&oacute;n en bytes</span>
                    </p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span>ALGORITMO_MEMORIA</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El tipo de algoritmo de administraci&oacute;n de memoria que se
                            va a utilizar (PARTICIONES/BS)</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span>ALGORITMO_REEMPLAZO</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El tipo de algoritmo de reemplazo de memoria que se va a
                            utilizar(FIFO/LRU)</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span>ALGORITMO_PARTICION_LIBRE</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El tipo de algoritmo de selecci&oacute;n de partici&oacute;n
                            libre a utilizar(FF/BF)</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">IP_BROKER</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El IP del servidor del proceso Broker</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span>PUERTO_BROKER</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El puerto del servidor del proceso Broker</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span>FRECUENCIA_COMPACTACION</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">Cantidad de b&uacute;squedas fallidas previa
                            compactaci&oacute;n</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c57" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">LOG_FILE</span></p>
                </td>
                <td class="c81" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c70" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">Path del archivo de log donde se almacenar&aacute; el log
                            obligatorio</span></p>
                </td>
            </tr>
        </tbody>
    </table>
    <p class="c2 c24"><span class="c3"></span></p>
    <p class="c2"><span class="c3">Queda a decisi&oacute;n del grupo el agregado de m&aacute;s par&aacute;metros al
            mismo. </span></p>
    <h3 class="c38 c17" id="h.3as4poj"><span class="c5">Ejemplo de Archivo de Configuraci&oacute;n</span></h3>
    <p class="c2 c97"><span class="c14 c27">TAMANO_MEMORIA</span><span
            class="c14">=2048<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">TAMANO_MINIMO_PARTICION</span><span
            class="c14">=32<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">ALGORITMO_MEMORIA</span><span
            class="c14">=BS<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">ALGORITMO_REEMPLAZO</span><span
            class="c14">=FIFO<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">ALGORITMO_PARTICION_LIBRE</span><span
            class="c14">=FF<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">IP_BROKER</span><span
            class="c14">=127.0.0.1<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">PUERTO_BROKER</span><span
            class="c14">=6009<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">FRECUENCIA_COMPACTACION</span><span class="c14">=3</span>
        <hr style="page-break-before:always;display:none;">
    </p>
    <h1 class="c20 c17" id="h.1pxezwc"><span class="c67 c27 c40 c48">Proceso Game Card</span></h1>
    <p class="c2"><span>Este m&oacute;dulo nos permitir&aacute; </span><span class="c40">implementar nuestro propio
            almacenamiento de archivos</span><span>, que almacene los datos de los distintos Pokemon que se encuentren
            en el mapa. Para esto, se deber&aacute; implementar el FileSystem </span><span>TALL_GRASS</span><span
            class="c3">&nbsp;explicado en los siguientes apartados.</span></p>
    <p class="c2"><span class="c3">Este proceso, se comunicar&aacute; con los dem&aacute;s de dos posibles
            maneras:</span></p>
    <ol class="c32 lst-kix_list_24-0 start" start="1">
        <li class="c25 c17"><span>A trav&eacute;s de la conexi&oacute;n con el Broker asoci&aacute;ndose globalmente a
                la cola de mensajes </span><span>NEW_POKEMON</span><span>, </span><span>CATCH_POKEMON</span><span
                class="c3">&nbsp; y GET_POKEMON.</span></li>
        <li class="c2 c47"><span class="c3">A trav&eacute;s de un socket de escucha en el cual podr&aacute; recibir
                mensajes de las colas de mensajes mencionadas en el punto anterior.</span></li>
    </ol>
    <p class="c2"><span class="c3">Cabe aclarar que el Proceso Game Card debe poder ejecutarse sin haber establecido la
            conexi&oacute;n con el Broker, es decir, si el Broker se encuentra sin funcionar, o se cae durante la
            ejecuci&oacute;n, el proceso Game Card debe seguir procesando sus funciones sin el mismo.</span></p>
    <p class="c2"><span>En caso que la conexi&oacute;n no llegue a realizarse o se caiga, el proceso Game Card
            deber&aacute; contar con un sistema de reintento de conexi&oacute;n cada X segundos configurado desde
            archivo de configuraci&oacute;n. </span><span class="c52">Esto permitir&aacute; que, en caso de caerse el
            Broker, este se inicie posteriormente al mismo; produciendo que el proceso Game Card pueda asociarse a las
            colas sin necesidad de reiniciarse.</span></p>
    <h2 class="c16" id="h.49x2ik5"><span class="c31">Tall Grass</span></h2>
    <p class="c115"><span class="c3">El FileSystem Tall Grass es un componente creado con prop&oacute;sitos
            acad&eacute;micos para que el alumno comprenda el funcionamiento b&aacute;sico de la gesti&oacute;n de
            archivos en un sistema operativo.</span></p>
    <p class="c50"><span class="c3">La estructura b&aacute;sica del mismo se basa en una estructura de &aacute;rbol de
            directorios para representar la informaci&oacute;n administrativa y los datos de los entidades/Pokemon en
            formato de archivos. El &aacute;rbol de directorios tomar&aacute; su punto de partida del punto de montaje
            del archivo de configuraci&oacute;n.</span></p>
    <p class="c50"><span class="c3">Durante las pruebas no se proveer&aacute;n archivos que tengan estados
            inconsistentes respecto del trabajo pr&aacute;ctico, por lo que no es necesario tomar en cuenta dichos
            casos.</span></p>
    <h3 class="c38 c17" id="h.2p2csry"><span class="c5">Metadata</span></h3>
    <p class="c69 c17"><span class="c3">Este archivo tendr&aacute; la informaci&oacute;n correspondiente a la cantidad
            de bloques y al tama&ntilde;o de los mismos dentro del File System.</span></p>
    <p class="c69"><span>Dentro del</span><span>&nbsp;</span><span class="c3">archivo se encontrar&aacute;n los
            siguiente campos:</span></p>
    <ul class="c32 lst-kix_list_10-0 start">
        <li class="c23"><span class="c40">Block_size</span><span class="c3">: Indica el tama&ntilde;o en bytes de cada
                bloque</span></li>
        <li class="c23"><span class="c40">Blocks</span><span class="c3">: Indica la cantidad de bloques del File
                System</span></li>
        <li class="c69 c47"><span class="c40">Magic_Number</span><span>: Un string fijo con el valor
                &ldquo;</span><span>TALL_GRASS</span><span class="c3">&rdquo;</span></li>
    </ul>
    <p class="c69"><span class="c3">Ej: </span></p>
    <p class="c26 c97"><span class="c14 c35">BLOCK_SIZE</span><span
            class="c14 c63">=64<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c35">BLOCKS</span><span
            class="c14 c63">=5192<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c35">MAGIC_NUMBER</span><span class="c14 c63">=TALL_GRASS</span></p>
    <p class="c69 c17"><span>Dicho &nbsp;archivo deber&aacute; encontrarse en la ruta </span><span
            class="c14">[</span><span class="c14">Punto_Montaje</span><span
            class="c36 c14 c78">]/Metadata/Metadata.bin</span></p>
    <h4 class="c11" id="h.147n2zr"><span class="c66 c45">Bitmap</span></h4>
    <p class="c69 c17"><span>Este ser&aacute; un archivo de tipo binario donde solamente existir&aacute; un
            bitmap</span><sup class="c83"><a href="#ftnt4" id="ftnt_ref4">[4]</a></sup><span class="c3">, el cual
            representar&aacute; el estado de los bloques dentro del FS, siendo un 1 que el bloque est&aacute; ocupado y
            un 0 que el bloque est&aacute; libre.</span></p>
    <p class="c69 c17"><span>La ruta del archivo de bitmap es: </span><span class="c14">[</span><span
            class="c14">Punto_Montaje</span><span class="c36 c14 c78">]/Metadata/Bitmap.bin</span></p>
    <h4 class="c11" id="h.3o7alnk"><span class="c66 c45">Files Metadata</span></h4>
    <p class="c17 c71"><span class="c3">Los archivos dentro del FS se encontrar&aacute;n en un path compuesto de la
            siguiente manera:</span></p>
    <p class="c60"><span class="c14">[</span><span class="c14">Punto_Montaje</span><span
            class="c36 c14 c78">]/Files/[Nombre_Archivo]</span></p>
    <p class="c69"><span class="c3">Donde el path del archivo incluye el archivo Metadata.</span></p>
    <p class="c60"><span class="c36 c14 c30">Ej:</span></p>
    <p class="c60 c58"><span class="c36 c14 c30">/mnt/TALL_GRASS/Files/Pikachu/Metadata.bin</span></p>
    <p class="c69"><span class="c3">Dentro del archivo Metadata.bin se encontrar&aacute;n los siguientes campos:</span>
    </p>
    <ul class="c32 lst-kix_list_10-0">
        <li class="c23"><span class="c40">Directory: </span><span class="c3">indica si el archivo en cuesti&oacute;n es
                un directorio o no (Y/N).</span></li>
        <li class="c23"><span class="c40">Size</span><span class="c3">: indica el tama&ntilde;o real del archivo en
                bytes (en caso de no ser un directorio).</span></li>
        <li class="c23"><span class="c40">Blocks</span><span>: es un array de n&uacute;meros que contiene el orden de
                los bloques en donde se encuentran los datos propiamente dichos de ese archivo (en caso de no ser un
                directorio).</span></li>
        <li class="c69 c47"><span class="c40">Open</span><span>: indica si el archivo se encuentra abierto (Y/N).</span>
        </li>
    </ul>
    <p class="c69"><span class="c36 c14 c78">Ej Directorio: </span></p>
    <p class="c60"><span class="c14 c35">DIRECTORY</span><span class="c14">=Y</span></p>
    <p class="c69"><span class="c36 c14 c78">Ej Archivo: </span></p>
    <p class="c60"><span class="c14 c35">DIRECTORY</span><span
            class="c14">=N<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c35">SIZE</span><span
            class="c14">=250<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c35">BLOCKS</span><span
            class="c14">=[40,21,82,3]<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c35">OPEN</span><span class="c36 c14 c78">=Y</span></p>
    <p class="c2"><span class="c3">De esta manera podremos formar el siguiente &aacute;rbol de archivos en donde la
            metadata dentro del directorio Files contiene un DIRECTORY con valor Y y Pikachu tiene un metadata con un
            DIRECTORY con el valor N.</span></p>
    <p class="c2 c97"><span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">/mnt/</span><span class="c14 c30">TALL_GRASS</span><span
            class="c14 c30">/Files/Metadata.bin</span><span><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">/mnt/</span><span class="c14 c30">TALL_GRASS</span><span
            class="c14 c30">/Files/Pikachu/Metadata.bin</span></p>
    <h3 class="c38 c17" id="h.23ckvvd"><span class="c5">Datos</span></h3>
    <p class="c69"><span class="c3">Los datos estar&aacute;n repartidos en archivos de texto nombrados con un
            n&uacute;mero, el cual representar&aacute; el n&uacute;mero de bloque. (Por ej 1.bin, 2.bin, 3.bin), </span>
    </p>
    <p class="c69"><span class="c3">Dichos archivos se encontraran dentro de la ruta:</span></p>
    <p class="c69"><span class="c14">[</span><span class="c14">Punto_Montaje</span><span
            class="c36 c14 c78">]/Blocks/[nroBloque].bin</span></p>
    <p class="c60"><span class="c36 c14 c30">Ej: </span></p>
    <p class="c60 c58"><span class="c36 c14 c30">/mnt/TALL_GRASS/Blocks/1.bin</span></p>
    <p class="c60 c58"><span class="c14 c30">/mnt/TALL_GRASS/Blocks/2.bin</span></p>
    <h2 class="c16" id="h.ihv636"><span class="c31">Lineamiento e Implementaci&oacute;n</span></h2>
    <p class="c2"><span class="c3">Este proceso gestionar&aacute; un Filesystem que ser&aacute; le&iacute;do e
            interpretado como un &aacute;rbol de directorios y sus archivos utilizando el Filesystem Tall Grass.</span>
    </p>
    <p class="c2"><span class="c3">A su vez, al iniciar el proceso Game Card se intentara suscribir globalmente al
            Broker a las siguientes colas de mensajes:</span></p>
    <ul class="c32 lst-kix_list_13-0">
        <li class="c25 c17"><span>NEW_POKEMON</span></li>
        <li class="c25 c17"><span>CATCH_POKEMON</span></li>
        <li class="c2 c47"><span>GET_POKEMON</span></li>
    </ul>
    <p class="c2"><span class="c3">Al suscribirse a cada una de las colas deber&aacute; quedarse a la espera de recibir
            un mensaje del Broker. Al recibir un mensaje de cualquier hilo se deber&aacute;:</span></p>
    <ol class="c32 lst-kix_list_11-0 start" start="1">
        <li class="c25 c17"><span>Informar al Broker la recepci&oacute;n del mismo (ACK).</span></li>
        <li class="c25 c17"><span>Crear un hilo que atienda dicha solicitud.</span></li>
        <li class="c2 c47"><span>Volver a estar a la escucha de nuevos mensajes de la cola de mensajes en
                cuesti&oacute;n.</span></li>
    </ol>
    <p class="c2"><span>Todo archivo dentro del file system tendr&aacute; un valor &ldquo;OPEN&rdquo; dentro de su
            metadata, que indicar&aacute; si actualmente hay alg&uacute;n proceso que se encuentra utilizando el mismo.
        </span><span class="c4">Bajo ning&uacute;n concepto se permitir&aacute; a dos procesos abrir el mismo archivo en
            simult&aacute;neo</span><span class="c3">, en caso que suceda esto se deber&aacute; informar el error
            pertinente por archivo de log o consola y reintentar la operaci&oacute;n luego del tiempo definido por
            archivo configuraci&oacute;n.</span></p>
    <h3 class="c38 c17" id="h.32hioqz"><span class="c5">Archivos Pokemon</span></h3>
    <p class="c2"><span class="c3">Cada archivo de tipo pokemon tendra internamente (por cada fila) la lista de
            posiciones en el mapa que se encuentra con la cantidad en dicha posici&oacute;n. De esta manera un posible
            archivo de pokemon puede ser:</span></p>
    <p class="c2"><span
            class="c14 c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1-1=10<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1-5=1<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3-1=2<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7-6=1000</span>
    </p>
    <p class="c2"><span class="c3">La inclusi&oacute;n de una nueva l&iacute;nea o eliminaci&oacute;n depende de la
            recepci&oacute;n de los distintos mensajes desde el Broker. &nbsp;</span></p>
    <p class="c2"><span class="c3">A continuaci&oacute;n se explicar&aacute; el funcionamiento que se debe realizar al
            recibir mensajes de alguna de estas colas.</span></p>
    <h3 class="c38 c17" id="h.1hmsyys"><span class="c5">New Pokemon</span></h3>
    <p class="c2"><span class="c3">Este mensaje cumplir&aacute; la funci&oacute;n de agregar la aparici&oacute;n de un
            nuevo pok&eacute;mon al mapa. Tendr&aacute; cuatro par&aacute;metros de entrada:</span></p>
    <ol class="c32 lst-kix_list_39-0 start" start="1">
        <li class="c25 c17"><span>ID del mensaje recibido.</span></li>
        <li class="c25 c17"><span>Pokemon a agregar.</span></li>
        <li class="c25 c17"><span>Posici&oacute;n del mapa.</span></li>
        <li class="c2 c47"><span>Cantidad de pok&eacute;mon en dicha posici&oacute;n a agregar.</span></li>
    </ol>
    <p class="c2"><span class="c3">Al recibir este mensaje se deber&aacute;n realizar las siguientes operaciones:</span>
    </p>
    <ol class="c32 lst-kix_list_30-0 start" start="1">
        <li class="c25 c17"><span>Verificar si el Pok&eacute;mon existe dentro de nuestro Filesystem. Para esto se
                deber&aacute; buscar dentro del directorio Pokemon si existe el archivo con el nombre de nuestro
                pok&eacute;mon. En caso de no existir se deber&aacute; crear.</span></li>
        <li class="c25 c17"><span>Verificar si se puede abrir el archivo (si no hay otro proceso que lo est&eacute;
                abriendo). En caso que el archivo se encuentre abierto se deber&aacute; reintentar la operaci&oacute;n
                luego de un tiempo definido en el archivo de configuraci&oacute;n.</span></li>
        <li class="c25 c17"><span class="c3">Verificar si las posiciones ya existen dentro del archivo. En caso de
                existir, se deben agregar la cantidad pasada por par&aacute;metro a la actual. En caso de no existir se
                debe agregar al final del archivo una nueva l&iacute;nea indicando la cantidad de pok&eacute;mon
                pasadas.</span></li>
        <li class="c25 c17"><span class="c3">Esperar la cantidad de segundos definidos por archivo de
                configuraci&oacute;n</span></li>
        <li class="c25 c17"><span>Cerrar el archivo.</span></li>
        <li class="c25 c17"><span>Conectarse al Broker</span><span>&nbsp;y enviar el mensaje a la Cola de Mensajes
            </span><span class="c4">APPEARED_POKEMON</span><span class="c4">&nbsp;</span><span>con los los datos:</span>
        </li>
    </ol>
    <ul class="c32 lst-kix_list_30-1 start">
        <li class="c76 c17"><span class="c3">ID del mensaje recibido.</span></li>
        <li class="c17 c76"><span class="c3">Pokemon.</span></li>
        <li class="c2 c88"><span class="c3">Posici&oacute;n del mapa.</span></li>
    </ul>
    <p class="c2"><span class="c3">En caso que no se pueda realizar la conexi&oacute;n con el Broker se debe informar
            por logs y continuar la ejecuci&oacute;n.</span></p>
    <h3 class="c38 c17" id="h.41mghml"><span class="c5">Catch Pokemon</span></h3>
    <p class="c2"><span class="c3">Este mensaje cumplir&aacute; la funci&oacute;n de indicar si es posible capturar un
            Pokemon, y capturarlo en tal caso. Para esto se recibir&aacute;n los siguientes par&aacute;metros:</span>
    </p>
    <ol class="c32 lst-kix_list_27-0 start" start="1">
        <li class="c25 c17"><span class="c3">ID del mensaje recibido.</span></li>
        <li class="c25 c17"><span class="c3">Pokemon a atrapar.</span></li>
        <li class="c2 c47"><span class="c3">Posici&oacute;n del mapa.</span></li>
    </ol>
    <p class="c2"><span class="c3">Al recibir este mensaje se deber&aacute;n realizar las siguientes operaciones:</span>
    </p>
    <ol class="c32 lst-kix_list_8-0 start" start="1">
        <li class="c25 c17"><span class="c3">Verificar si el Pok&eacute;mon existe dentro de nuestro Filesystem. Para
                esto se deber&aacute; buscar dentro del directorio Pokemon, si existe el archivo con el nombre de
                nuestro pok&eacute;mon. En caso de no existir se deber&aacute; informar un error.</span></li>
        <li class="c25 c17"><span class="c3">Verificar si se puede abrir el archivo (si no hay otro proceso que lo
                est&eacute; abriendo). En caso que el archivo se encuentre abierto se deber&aacute; reintentar la
                operaci&oacute;n luego de un tiempo definido en el archivo de configuraci&oacute;n.</span></li>
        <li class="c25 c17"><span class="c3">Verificar si las posiciones ya existen dentro del archivo. En caso de no
                existir se debe informar un error.</span></li>
        <li class="c25 c17"><span class="c3">En caso que la cantidad del Pok&eacute;mon sea &ldquo;1&rdquo;, se debe
                eliminar la l&iacute;nea. En caso contrario se debe decrementar la cantidad en uno.</span></li>
        <li class="c25 c17"><span class="c3">Esperar la cantidad de segundos definidos por archivo de
                configuraci&oacute;n</span></li>
        <li class="c25 c17"><span>Cerrar el archivo.</span></li>
        <li class="c2 c47"><span>Conectarse al Broker</span><span>&nbsp;y enviar el mensaje indicando el resultado
                correcto.</span></li>
    </ol>
    <p class="c2"><span>Todo resultado, sea correcto o no, deber&aacute; realizarse conectandose al Broker y enviando un
            mensaje a la Cola de Mensajes </span><span class="c4">CAUGHT_POKEMON</span><span
            class="c4">&nbsp;</span><span class="c3">indicando:</span></p>
    <ol class="c32 lst-kix_list_37-0 start" start="1">
        <li class="c25 c17"><span>ID del mensaje recibido originalmente.</span></li>
        <li class="c2 c47"><span>Resultado</span><span>.</span></li>
    </ol>
    <p class="c2"><span class="c3">En caso que no se pueda realizar la conexi&oacute;n con el Broker se debe informar
            por logs y continuar la ejecuci&oacute;n.</span></p>
    <h3 class="c38 c17" id="h.2grqrue"><span class="c5">Get Pokemon</span></h3>
    <p class="c2"><span class="c3">Este mensaje cumplir&aacute; la funci&oacute;n de obtener todas las posiciones y su
            cantidad de un Pok&eacute;mon espec&iacute;fico. Para esto recibir&aacute;:</span></p>
    <ol class="c32 lst-kix_list_23-0 start" start="1">
        <li class="c25 c17"><span>El identificador del mensaje recibido.</span></li>
        <li class="c2 c47"><span>Pok&eacute;mon a devolver.</span></li>
    </ol>
    <p class="c2"><span class="c3">Al recibir este mensaje se deber&aacute;n realizar las siguientes operaciones:</span>
    </p>
    <ol class="c32 lst-kix_list_20-0 start" start="1">
        <li class="c25 c17"><span>Verificar si el Pok&eacute;mon existe dentro de nuestro Filesystem. Para esto se
                deber&aacute; buscar dentro del directorio Pokemon, si existe el archivo con el nombre de nuestro
                pok&eacute;mon. En caso de no existir se deber&aacute; informar el mensaje sin posiciones ni
                cantidades.</span></li>
        <li class="c25 c17"><span>Verificar si se puede abrir el archivo (si no hay otro proceso que lo est&eacute;
                abriendo). En caso que el archivo se encuentre abierto se deber&aacute; reintentar la operaci&oacute;n
                luego de un tiempo definido por configuraci&oacute;n.</span></li>
        <li class="c25 c17"><span class="c3">Obtener todas las posiciones y cantidades de Pokemon requerido.</span></li>
        <li class="c25 c17"><span>Esperar la cantidad de segundos definidos por archivo de configuraci&oacute;n</span>
        </li>
        <li class="c25 c17"><span>Cerrar el archivo.</span></li>
        <li class="c2 c47"><span>Conectarse al Broker y enviar el mensaje con todas las posiciones y su cantidad.</span>
        </li>
    </ol>
    <p class="c2"><span>En caso que se encuentre por lo menos una posici&oacute;n para el Pok&eacute;mon solicitado se
            deber&aacute; enviar un mensaje al Broker a la Cola de Mensajes </span><span
            class="c4">LOCALIZED_POKEMON</span><span class="c4">&nbsp;</span><span class="c3">indicando:</span></p>
    <ol class="c32 lst-kix_list_37-0" start="3">
        <li class="c25 c17"><span class="c3">ID del mensaje recibido originalmente.</span></li>
        <li class="c25 c17"><span class="c3">El Pok&eacute;mon solicitado.</span></li>
        <li class="c2 c47"><span>La lista de posiciones y la </span><span>cantidad de posiciones X e Y </span><span>de
                cada una de ellas en el mapa.</span></li>
    </ol>
    <p class="c2"><span class="c3">En caso que no se pueda realizar la conexi&oacute;n con el Broker se debe informar
            por logs y continuar la ejecuci&oacute;n.</span></p>
    <p class="c2 c24"><span class="c3"></span></p>
    <h2 class="c16" id="h.3cnlyrbsrzs5"><span class="c31">Archivo de Configuraci&oacute;n</span></h2><a
        id="t.6440814963bde332fbcfcda7fa5ef1ccb77409fd"></a><a id="t.1"></a>
    <table class="c37">
        <tbody>
            <tr class="c10">
                <td class="c46 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Campo</span></p>
                </td>
                <td class="c51 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Tipo</span></p>
                </td>
                <td class="c6 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Descripci&oacute;n</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c46" colspan="1" rowspan="1">
                    <p class="c7"><span>TIEMPO_DE_REINTENTO_CONEXION</span></p>
                </td>
                <td class="c51" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c6" colspan="1" rowspan="1">
                    <p class="c12"><span>Tiempo en segundos en el cual el proceso debe
                        </span><span>reintentar</span><span class="c3">&nbsp;conectarse al broker.</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c46" colspan="1" rowspan="1">
                    <p class="c7"><span>TIEMPO_DE_REINTENTO_OPERACION</span></p>
                </td>
                <td class="c51" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c6" colspan="1" rowspan="1">
                    <p class="c12"><span>Tiempo en segundos en el cual el proceso debe
                        </span><span>reintentar</span><span class="c3">&nbsp;reabrir el archivo que se encontraba
                            abierto.</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c46" colspan="1" rowspan="1">
                    <p class="c7"><span>TIEMPO_RETARDO_OPERACION</span></p>
                </td>
                <td class="c51" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c6" colspan="1" rowspan="1">
                    <p class="c12"><span class="c3">Tiempo en segundos por los cuales el hilo deber&aacute; mantener el
                            archivo abierto a fin de simular accesos a disco.</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c46" colspan="1" rowspan="1">
                    <p class="c7"><span>PUNTO_MONTAJE_TALLGRASS</span></p>
                </td>
                <td class="c51" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c6" colspan="1" rowspan="1">
                    <p class="c12"><span class="c3">Punto en el cual se va a inicializar el file system.</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c46" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">IP_BROKER</span></p>
                </td>
                <td class="c51" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c6" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El IP del servidor del proceso Broker</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c46" colspan="1" rowspan="1">
                    <p class="c7"><span>PUERTO_BROKER</span></p>
                </td>
                <td class="c51" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c6" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El puerto del servidor del proceso Broker</span></p>
                </td>
            </tr>
        </tbody>
    </table>
    <p class="c2 c24"><span class="c3"></span></p>
    <p class="c2"><span class="c3">Queda a decisi&oacute;n del grupo el agregado de m&aacute;s par&aacute;metros al
            mismo. </span></p>
    <h3 class="c38 c17" id="h.3fwokq0"><span class="c73">Ejemplo de Archivo de Configuraci&oacute;n</span></h3>
    <p class="c2 c97"><span class="c14 c27">TIEMPO_DE_REINTENTO_CONEXION</span><span
            class="c14">=10<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">TIEMPO_DE_REINTENTO_OPERACION</span><span
            class="c14">=5<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">TIEMPO_RETARDO_OPERACION</span><span>=5<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">PUNTO_MONTAJE_TALLGRASS</span><span
            class="c14">=/home/utnso/desktop/tall-grass<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">IP_BROKER</span><span
            class="c14">=127.0.0.1<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c27">PUERTO_BROKER</span><span class="c36 c14 c78">=6009</span></p>
    <hr style="page-break-before:always;display:none;">
    <p class="c2 c24"><span class="c3"></span></p>
    <h1 class="c20 c17" id="h.1v1yuxt"><span class="c67 c27 c40 c48">Proceso Team</span></h1>
    <p class="c2"><span>Este proceso ser&aacute; el encargado de administrar distintos entrenadores
            &ldquo;</span><span>planific&aacute;ndolos</span><span class="c3">&rdquo; dentro de un mapa de dos
            coordenadas. Cada entrenador tendr&aacute; objetivos particulares en los cuales deber&aacute;n atrapar
            distintos Pok&eacute;mon, los cuales ser&aacute;n configurados por archivos de configuraci&oacute;n. Cabe
            aclarar que un entrenador no podr&aacute; atrapar mas pokemones de los que indique su objetivo, por ejemplo
            si su objetivo es atrapar tres pokemones cualesquiera, no podr&aacute; atrapar m&aacute;s de tres, por
            m&aacute;s que no sean los tres que &eacute;l necesita.</span></p>
    <h2 class="c16" id="h.4f1mdlm"><span class="c31">Lineamiento e Implementaci&oacute;n</span></h2>
    <p class="c2"><span class="c3">El objetivo de este proceso es verificar la aparici&oacute;n de un nuevo
            Pok&eacute;mon y, en caso de que alg&uacute;n entrenador requiera del mismo para el cumplimiento de su
            objetivo, planificar al entrenador m&aacute;s cercano libre se mueva a dicha posici&oacute;n a atraparlo.
            Este proceso se comunicar&aacute; de dos posibles maneras:</span></p>
    <ol class="c32 lst-kix_khs4csfq7wct-0 start" start="1">
        <li class="c25 c17"><span>A trav&eacute;s de la conexi&oacute;n con el Broker asoci&aacute;ndose globalmente a
                la cola de mensajes </span><span>APPEARED_POKEMON</span><span>,
            </span><span>LOCALIZED_POKEMON</span><span>&nbsp; y </span><span>CAUGHT_POKEMON</span><span>&nbsp;.</span>
        </li>
        <li class="c2 c47"><span>A trav&eacute;s de un socket de escucha en el cual podr&aacute; recibir mensajes de
                apariciones de Pok&eacute;mon.</span></li>
    </ol>
    <p class="c2"><span class="c3">Cabe aclarar que el Proceso Team debe poder ejecutarse sin haber establecido la
            conexi&oacute;n con el Broker. Es decir, si el broker se encuentra sin funcionar o se cae durante la
            ejecuci&oacute;n, el proceso Team debe seguir procesando sus funciones sin el mismo. Para esto, se
            contar&aacute;n con funciones default para aquellos mensajes que el Proceso Team env&iacute;e directamente
            al Broker.</span></p>
    <p class="c2"><span class="c3">En caso que la conexi&oacute;n no llegue a realizarse o se caiga, el proceso Team
            deber&aacute; contar con un sistema de reintento de conexi&oacute;n cada X segundos configurado desde
            archivo de configuraci&oacute;n.</span></p>
    <h3 class="c38 c17" id="h.2u6wntf"><span class="c5">Planificaci&oacute;n</span></h3>
    <p class="c2"><span class="c3">Como dijimos anteriormente, los distintos entrenadores se configuran desde archivo de
            configuraci&oacute;n. Al iniciar el proceso, se deber&aacute; crear un hilo por cada entrenador existente y
            el proceso Team deber&aacute; conocer cu&aacute;les y qu&eacute; cantidad de Pok&eacute;mon de cada especie
            requiere en total para cumplir el objetivo global. </span></p>
    <p class="c2"><span>Se dice que un proceso Team cumpli&oacute; su objetivo global cuando todos sus entrenadores
            obtuvieron los Pok&eacute;mon que requieren. Una vez alcanzado el objetivo se
        </span><span>deber&aacute;</span><span>&nbsp;informar por archivo de log y por pantalla el resultado alcanzado y
            finalizar el proceso. Esta finalizaci&oacute;n a diferencia de la teor&iacute;a no
        </span><span>liberar&aacute;</span><span class="c3">&nbsp;los recursos obtenidos (Pok&eacute;mons).</span></p>
    <p class="c2"><span class="c3">Al aparecer un Pok&eacute;mon (por cualquiera de los dos m&eacute;todos antes
            explicados) s&oacute;lo se podr&aacute; planificar a un entrenador hacia dicha posici&oacute;n
            independientemente de cu&aacute;ntos Pok&eacute;mon de dicha especie haya en la posici&oacute;n en la que
            apareci&oacute;. </span></p>
    <p class="c2"><span>Para poder planificar un entrenador, se seleccionar&aacute; el hilo del entrenador m&aacute;s
            cercano al Pok&eacute;mon. Cada movimiento en el mapa responder&aacute; a un ciclo de CPU, y este NO
        </span><span>realizar&aacute;</span><span>&nbsp;movimientos diagonales para llegar a la
        </span><span>posici&oacute;n</span><span class="c3">&nbsp;deseada. Para simular m&aacute;s a la realidad esta
            funcionalidad, se deber&aacute; agregar un retardo de X segundos configurado por archivo de
            configuraci&oacute;n.</span></p>
    <p class="c2"><span class="c3">Para planificar a los distintos entrenadores se utilizar&aacute;n los algoritmos
            FIFO, Round Robin y Shortest job first con y sin desalojo. Para este &uacute;ltimo algoritmo se desconoce la
            pr&oacute;xima rafaga, por lo que se deber&aacute; utilizar la f&oacute;rmula de la media exponencial. A su
            vez, la estimaci&oacute;n inicial para todos los entrenadores ser&aacute; la misma y deber&aacute; poder ser
            modificable por archivo de configuraci&oacute;n</span></p>
    <h3 class="c38 c17" id="h.19c6y18"><span class="c5">Diagrama de estados de un Entrenador</span></h3>
    <p class="c2"><span>Cada entrenador al iniciar en el sistema entrar&aacute; en estado New. A medida que el Team
            empiece a recibir distintos Pok&eacute;mon en el mapa despertar&aacute; a los distintos entrenadores en
            estado New o en </span><span>Blocked</span><span class="c3">&nbsp;(que est&eacute;n esperando para procesar)
            pasandolos a Ready. Siempre se planificar&aacute; aquel entrenador que se encuentre sin estar realizando
            ninguna operaci&oacute;n activamente y, en caso de existir m&aacute;s de uno, sea el que m&aacute;s cerca se
            encuentre del objetivo. </span></p>
    <p class="c2"><span class="c3">A medida que cada entrenador se planifique (ya sea para moverse, intercambiar o
            atrapar un Pok&eacute;mon) entrar&aacute;n en estado exec. En el contexto de nuestro trabajo practico no
            contemplaremos el multiprocesamiento, esto implica que solo UN entrenador podr&aacute; estar en estado Exec
            en determinado tiempo.</span></p>
    <p class="c2"><span class="c3">Cuando un entrenador en estado Exec finalice su recorrido y su ejecuci&oacute;n
            planificada entrar&aacute; en un estado bloqueados. Este estado implica que el entrenador no tiene
            m&aacute;s tareas para realizar moment&aacute;neamente.</span></p>
    <p class="c2"><span class="c3">Cuando un entrenador en estado Exec cumpla todos sus objetivos, pasar&aacute; a
            estado Exit. Cuando todos los entrenadores dentro de un Team se encuentren en Exit, se considera que el
            proceso Team cumpli&oacute; el objetivo global.</span></p>
    <p class="c2"><span class="c3">Cuando se detecte situaciones de Deadlock deber&aacute;n estar ambos en estado
            bloqueado. En este momento, uno de ellos se pasa a estado Ready con el objetivo que se lo planifique hasta
            la posici&oacute;n del otro. Al llegar a la misma posici&oacute;n, se deber&aacute; realizar el intercambio.
            Cada intercambio ocupara 5 ciclos de CPU. Cada intercambio solo involucra a dos Pok&eacute;mon.</span></p>
    <p class="c2"><span class="c3">Al finalizar el intercambio se verificar&aacute; si alguno est&aacute; en condiciones
            de ir a Exit y de no ser as&iacute; &nbsp;ir&aacute;n nuevamente a estado bloqueado. A su vez, cada
            acci&oacute;n de movimiento o env&iacute;o de mensaje al Broker consumir&aacute; un ciclo de CPU.</span></p>
    <p class="c2"><span class="c3">Cada vez que un entrenador realice una operaci&oacute;n de captura sobre un
            Pok&eacute;mon se lo bloquear&aacute; a la espera del resultado no pudiendo volver a operar hasta obtener el
            mismo.</span></p>
    <p class="c2"><span class="c3">Adjuntamos un diagrama de estados con lo anteriormente mencionado.</span></p>
    <p class="c42 c17"><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 482.01px; height: 153.52px;"><img
                alt="" src="images/image3.png"
                style="width: 482.01px; height: 153.52px; margin-left: 0.00px; margin-top: 0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></p>
    <p class="c17 c93"><span class="c3">Cabe aclarar que el diagrama antes descrito es similar al visto en la
            teor&iacute;a pero agrega transiciones propias del contexto de este Trabajo pr&aacute;ctico.</span></p>
    <h3 class="c38 c17" id="h.3tbugp1"><span class="c5">Competici&oacute;n y Deadlock</span></h3>
    <p class="c2"><span class="c3">Dado que pueden existir varios procesos Team dentro de nuestro sistema, puede darse
            la posibilidad de que varios de ellos requieran una especie de un Pokemon y no exista la misma cantidad de
            ellos en el sistema. Este flujo es el esperado y nos permitir&aacute; probar los distintos algoritmos de
            planificaci&oacute;n con sus ventajas y desventajas.</span></p>
    <p class="c2"><span class="c3">Para comparar los mismos el proceso Team al cumplir su objetivo deber&aacute;
            informar:</span></p>
    <ol class="c32 lst-kix_list_3-0 start" start="1">
        <li class="c25 c17"><span>Cantidad de ciclos de CPU totales.</span></li>
        <li class="c25 c17"><span>Cantidad de cambios de contexto realizados.</span></li>
        <li class="c25 c17"><span>Cantidad de ciclos de CPU realizados por entrenador.</span></li>
        <li class="c2 c47"><span>Deadlocks producidos y resueltos (Spoiler Alert).</span></li>
    </ol>
    <p class="c2"><span class="c3">Dado que el proceso Team conoce cuantos Pokemon de cada especie necesita globalmente,
            cuantos de cada uno ha atrapado y planifica al entrenador m&aacute;s cercano libre, puede darse el caso que
            un entrenador que no requiere una especie de Pok&eacute;mon termine capturandolo, impidiendo a otro del
            mismo equipo que si lo necesita, obtenga el mismo.</span></p>
    <p class="c2"><span class="c3">En estos casos se producir&aacute; un caso de Deadlock, en el cual el proceso Team no
            podr&aacute; finalizar debido a que varios de sus entrenadores est&aacute;n en un estado de Interbloqueo. Es
            responsabilidad de cada grupo definir un algoritmo para detectar estos casos para poder resolverlos.</span>
    </p>
    <p class="c2"><span>Cuando se detecte dichos casos, se deber&aacute; bloquear uno de los entrenadores y planificar
            al/los otro/</span><span>s a</span><span class="c3">&nbsp;la posici&oacute;n del primero para generar un
            &ldquo;intercambio&rdquo; (cada intercambio implica que cada entrenador entregue un Pok&eacute;mon al otro
            uno de ellos).</span></p>
    <h3 class="c38 c17" id="h.28h4qwu"><span class="c5">Tipo de mensajes</span></h3>
    <p class="c2"><span>El proceso Team manejara </span><span>5 tipos de mensajes hacia el Broker, todos por
            suscripci&oacute;n global</span><span class="c3">&nbsp;por mensajes correlativos.</span></p>
    <h4 class="c11" id="h.nmf14n"><span class="c66 c45">Appeared Pokemon</span></h4>
    <p class="c2"><span class="c3">Este mensaje permitir&aacute; la inclusi&oacute;n en el proceso Team de un nuevo
            Pok&eacute;mon en el mapa. Esto se podr&aacute; producir de las dos maneras indicadas anteriormente.</span>
    </p>
    <p class="c2"><span class="c3">Al llegar este mensaje, el proceso Team deber&aacute; verificar si requiere atrapar
            el mismo controlando los Pokemon globales necesarios y los ya atrapados. No se debe poder atrapar mas
            Pokemon de una especie de los requeridos globalmente.</span></p>
    <p class="c2"><span class="c3">En caso que se requiera el mismo, se debe agregar a la lista de Pok&eacute;mon
            requeridos y en el momento que un entrenador se encuentre en estado &ldquo;Dormido&rdquo; o
            &ldquo;Libre&rdquo; debe planificarlo para ir a atraparlo.</span></p>
    <p class="c2"><span class="c3">En este mensaje se recibir&aacute;n los siguientes par&aacute;metros:</span></p>
    <ul class="c32 lst-kix_list_41-0 start">
        <li class="c25 c17"><span>Especie de Pokemon.</span></li>
        <li class="c2 c47"><span>Posici&oacute;n del Pokemon.</span></li>
    </ul>
    <h4 class="c11" id="h.37m2jsg"><span class="c66 c45">Get Pokemon</span></h4>
    <p class="c2"><span>Este mensaje se ejecutar&aacute; al iniciar el proceso Team. El objetivo del mismo es obtener
            todas las locaciones de una especie de Pokemon. De esta manera, al iniciar el proceso, por cada especie de
            Pok&eacute;mon requerido se debe enviar un mensaje a la cola de mensajes
        </span><span>GET_POKEMON</span><span class="c3">&nbsp;del Broker.</span></p>
    <p class="c2"><span class="c3">Para esto se deben ejecutar los siguientes pasos:</span></p>
    <ol class="c32 lst-kix_list_26-0 start" start="1">
        <li class="c25 c17"><span>Enviar el mensaje a la cola de mensajes
            </span><span>GET_POKEMON</span><span>&nbsp;indicando cual es la especie del
            </span><span>Pokemon</span><span>.</span></li>
        <li class="c2 c47"><span>Obtener el ID del mensaje anterior desde el Broker.</span></li>
    </ol>
    <p class="c2"><span class="c3">En caso que el Broker no se encuentre funcionando o la conexi&oacute;n inicial falle,
            se deber&aacute; tomar como comportamiento Default que no existen locaciones para la especie
            requerida.</span></p>
    <h4 class="c11" id="h.1mrcu09"><span class="c66 c45">Catch Pokemon</span></h4>
    <p class="c2"><span>Este mensaje se ejecutar&aacute; al intentar atrapar a un Pok&eacute;mon (cuando un entrenador
            llegue a la posici&oacute;n del mismo). Para esto, se enviar&aacute; un mensaje a la cola de mensajes
        </span><span>CATCH_POKEMON</span><span class="c3">&nbsp;del Broker.</span></p>
    <p class="c2"><span class="c3">Para esto, se deben ejecutar los siguientes pasos:</span></p>
    <ol class="c32 lst-kix_list_17-0 start" start="1">
        <li class="c25 c17"><span>Enviar el mensaje a la cola de mensajes
            </span><span>CATCH_POKEMON</span><span>&nbsp;indicando cual es la especie del Pok&eacute;mon y la
                posici&oacute;n del mismo.</span></li>
        <li class="c25 c17"><span>Obtener el ID del mensaje anterior desde el Broker y guardarlo a la espera de la
                llegada de la respuesta en </span><span>CAUGHT_POKEMON</span><span>. </span></li>
        <li class="c2 c47"><span>Bloquear al entrenador en cuesti&oacute;n a la espera del resultado del mensaje. Este
                entrenador no podr&aacute; volver a ejecutar hasta que se reciba el resultado.</span></li>
    </ol>
    <p class="c2"><span class="c3">En caso que el Broker no se encuentre funcionando o la conexi&oacute;n inicial falle,
            se deber&aacute; tomar como comportamiento Default que el Pok&eacute;mon ha sido atrapado con
            &eacute;xito.</span></p>
    <h4 class="c11" id="h.46r0co2"><span class="c66 c45">Localized Pok&eacute;mon </span></h4>
    <p class="c2"><span>El proceso Team se </span><span>suscribir&aacute;</span><span class="c3">&nbsp;de manera global
            a esta cola de mensajes. Al recibir uno de los mismos deber&aacute; realizar los siguientes pasos:</span>
    </p>
    <ol class="c32 lst-kix_list_18-0 start" start="1">
        <li class="c25 c17"><span>Verificar si ya recibi&oacute; en alg&uacute;n momento un mensaje de la especie del
                Pok&eacute;mon asociado al mensaje. Si es as&iacute;, descarta el mensaje </span><span>(ya sea Appeared
                o Localized).</span></li>
        <li class="c2 c47"><span>En caso de que nunca lo haya recibido, realiza las mismas operatorias que para
            </span><span>APPEARED_POKEMON</span><span>&nbsp;por cada coordenada del pokemon.</span></li>
    </ol>
    <h4 class="c11" id="h.2lwamvv"><span class="c66 c45">Caught Pok&eacute;mon </span></h4>
    <p class="c2"><span>El proceso Team se </span><span>suscribir&aacute;</span><span class="c3">&nbsp;de manera global
            a esta cola de mensajes. Al recibir uno de los mismos deber&aacute; realizar los siguientes pasos:</span>
    </p>
    <ol class="c32 lst-kix_list_32-0 start" start="1">
        <li class="c25 c17"><span>Validar si el id de mensaje correlativo del mensaje corresponde a uno pendiente de
                respuesta generado por la la instrucci&oacute;n </span><span>CATCH_POKEMON</span><span>&nbsp;antes
                descrita. Si no corresponde a ninguno, ignorar el mensaje.</span></li>
        <li class="c2 c47"><span>En caso que corresponda se deber&aacute; validar si el resultado del mensaje es
                afirmativo (se atrap&oacute; el Pok&eacute;mon). Si es as&iacute; se debe asignar al entrenador
                bloqueado el Pok&eacute;mon y habilitarlo a poder volver operar.</span></li>
    </ol>
    <h2 class="c16" id="h.111kx3o"><span class="c31">Logs obligatorios</span></h2>
    <p class="c2"><span>Para permitir la verificaci&oacute;n/validaci&oacute;n del m&oacute;dulo se exigir&aacute; tener
            un archivo de log espec&iacute;fico e independiente que contenga la informaci&oacute;n indicada en esta
            secci&oacute;n. </span><span class="c4">No se permite la inclusi&oacute;n de otros mensajes y
            exclusi&oacute;n de ninguno de los mismos</span><span>&nbsp;(la falta o agregado de alguno puede implicar la
            desaprobaci&oacute;n del grupo). Dado que el log ser&aacute; el medio de validaci&oacute;n del trabajo
            pr&aacute;ctico </span><span class="c4">se exige no utilizar la consola como medio de logueo</span><span
            class="c3">. Cada operaci&oacute;n debe loguearse en una &uacute;nica l&iacute;nea indicando la misma y sus
            datos, en caso que el grupo desee loguear contenido extra deber&aacute; realizarlo en un archivo
            independiente.</span></p>
    <p class="c2"><span class="c3">Cabe aclarar que cada proceso Team deber&aacute; tener su propio archivo de Log. Por
            lo tanto, dado que puede darse el caso que se ejecuten varios procesos Team sobre el mismo ordenador se
            deber&aacute; indicar el archivo de log que se utilizar&aacute; para cada uno por archivo de
            configuraci&oacute;n.</span></p>
    <p class="c2"><span class="c3">Las acciones a loguear en este archivo son:</span></p>
    <ol class="c32 lst-kix_list_4-0 start" start="1">
        <li class="c25 c17"><span>Cambio de un entrenador de cola de planificaci&oacute;n (indicando la raz&oacute;n del
                porqu&eacute;).</span></li>
        <li class="c25 c17"><span>Movimiento de un entrenador (indicando la ubicaci&oacute;n a la que se
                movi&oacute;).</span></li>
        <li class="c25 c17"><span>Operaci&oacute;n de atrapar (indicando la ubicaci&oacute;n y el pokemon a
                atrapar).</span></li>
        <li class="c25 c17"><span>Operaci&oacute;n de intercambio (indicando entrenadores involucrados).</span></li>
        <li class="c25 c17"><span>Inicio de algoritmo de detecci&oacute;n de deadlock.</span></li>
        <li class="c25 c17"><span>Resultado de algoritmo de detecci&oacute;n de deadlock.</span></li>
        <li class="c25 c17"><span>Llegada de un mensaje (indicando el tipo del mismo y sus datos).</span></li>
        <li class="c25 c17"><span>Resultado del Team (especificado anteriormente).</span></li>
        <li class="c25 c17"><span>Errores de comunicaci&oacute;n con el Broker (indicando que se realizar&aacute; la
                operaci&oacute;n por default).</span></li>
        <li class="c25 c17"><span>Inicio de proceso de reintento de comunicaci&oacute;n con el Broker.</span></li>
        <li class="c2 c47"><span class="c3">Resultado de proceso de reintento de comunicaci&oacute;n con el
                Broker.</span></li>
    </ol>
    <hr style="page-break-before:always;display:none;">
    <p class="c2 c24"><span class="c3"></span></p>
    <h2 class="c16" id="h.3l18frh"><span class="c31">Archivo de Configuraci&oacute;n</span></h2><a
        id="t.25ae9ca60fc2ea1db1696495fd54fd57e8af1dfe"></a><a id="t.2"></a>
    <table class="c91">
        <tbody>
            <tr class="c10">
                <td class="c44 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Campo</span></p>
                </td>
                <td class="c87 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Tipo</span></p>
                </td>
                <td class="c41 c64" colspan="1" rowspan="1">
                    <p class="c86"><span class="c3">Descripci&oacute;n</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>POSICIONES_ENTRENADORES</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Lista de lista]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c12"><span class="c3">Contiene una lista de las posiciones de los entrenadores. </span>
                    </p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>POKEMON_ENTRENADORES</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Lista de lista]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c12"><span>Contiene una lista de los </span><span>pokemon</span><span class="c3">&nbsp;de
                            cada entrenadores. </span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>OBJETIVOS_ENTRENADORES</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Lista de lista]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c12"><span>Contiene una lista de los </span><span>pokemon</span><span class="c3">&nbsp;que
                            cada entrenador debe obtener. </span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>TIEMPO_RECONEXION</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c12"><span>Tiempo en segundos en el cual el proceso debe
                        </span><span>reintentar</span><span class="c3">&nbsp;conectarse al broker.</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>RETARDO_CICLO_CPU</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c12"><span class="c3">Tiempo en segundos para el retardo de la ejecuci&oacute;n de cada
                            ciclo de cpu</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>ALGORITMO_PLANIFICACION</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El tipo de algoritmo de planificaci&oacute;n que se va a utilizar
                            (FIFO/RR/SJF-CD/SJF-SD)</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">QUANTUM</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El valor del quantum en caso de que el algoritmo utilice
                            RR.</span></p>
                </td>
            </tr>
            <tr class="c84">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">ALPHA</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El valor del alpha en caso de que el algoritmo utilice
                            SJF.</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">IP_BROKER</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El IP del servidor del proceso Broker</span></p>
                </td>
            </tr>
            <tr class="c110">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>ESTIMACION_INICIAL</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El valor de la estimaci&oacute;n inicial para SJF en caso de que
                            aplique</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span>PUERTO_BROKER</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">El puerto del servidor del proceso Broker</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c44" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">LOG_FILE</span></p>
                </td>
                <td class="c87" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c41" colspan="1" rowspan="1">
                    <p class="c7 c17"><span class="c3">Path del archivo de log donde se almacenar&aacute; el log
                            obligatorio</span></p>
                </td>
            </tr>
        </tbody>
    </table>
    <p class="c2 c24"><span class="c3"></span></p>
    <p class="c2"><span class="c3">Queda a decisi&oacute;n del grupo el agregado de m&aacute;s par&aacute;metros al
            mismo. </span></p>
    <h3 class="c38 c17" id="h.206ipza"><span class="c5">Ejemplo de Archivo de Configuraci&oacute;n</span></h3>
    <p class="c2 c58"><span class="c14 c21">POSICIONES_ENTRENADORES</span><span
            class="c14 c30">=[1|2,3|7,5|5]<br></span><span class="c14 c21">POKEMON_ENTRENADORES</span><span
            class="c14 c30">=[</span><span class="c14 c30">Pikachu|Squirtle|Pidgey</span><span
            class="c14 c30">,</span><span class="c14 c30">Squirtle</span><span class="c14 c30">|Charmander,
            Bulbasaur]<br></span><span class="c14 c21">OBJETIVOS_ENTRENADORES</span><span
            class="c14 c30">=[Pikachu|</span><span class="c14 c30">Pidgey</span><span
            class="c14 c30">|Charmander|Bulbasaur, Pikachu|Charmander|Charmander,Squirtle|Bulbasaur]<br></span><span
            class="c14 c21">TIEMPO_RECONEXION</span><span class="c14 c30">=30<br></span><span
            class="c14 c21">RETARDO_CICLO_CPU</span><span class="c14 c30">=2<br></span><span
            class="c14 c21">ALGORITMO_PLANIFICACION</span><span class="c14 c30">=RR<br></span><span
            class="c14 c21">QUANTUM</span><span class="c14 c30">=2<br></span><span
            class="c14 c21">ESTIMACION_INICIAL</span><span class="c14 c30">=0<br></span><span
            class="c14 c21">IP_BROKER</span><span class="c14 c30">=127.0.0.1<br></span><span
            class="c14 c21">PUERTO_BROKER</span><span class="c14 c30">=5002<br></span><span
            class="c14 c21">LOG_FILE</span><span class="c36 c14 c30">=/home/utnso/log_team1.txt</span></p>
    <p class="c2 c24 c58"><span class="c36 c14 c30"></span></p>
    <p class="c2 c58"><span class="c14 c21">POSICIONES_ENTRENADORES</span><span class="c14 c30">=[1|2,3|7,5|5
            ]<br></span><span class="c14 c21">POKEMON_ENTRENADORES</span><span
            class="c14 c30">=[Pikachu|Squirtle|Pidgey,Squirtle|Charmander, Bulbasaur]<br></span><span
            class="c14 c21">OBJETIVOS_ENTRENADORES</span><span class="c14 c30">=[Pikachu|Pikachu|Squirtle|Pidgey,
            Pikachu|Charmander|Charmander, Squirtle|Bulbasaur]<br></span><span
            class="c14 c21">TIEMPO_RECONEXION</span><span class="c14 c30">=30<br></span><span
            class="c14 c21">RETARDO_CICLO_CPU</span><span class="c14 c30">=2<br></span><span
            class="c14 c21">ALGORITMO_PLANIFICACION</span><span class="c14 c30">=SJF-CD<br></span><span
            class="c14 c21">QUANTUM</span><span class="c14 c30">=0<br></span><span
            class="c14 c30">ESTIMACION_INICIAL</span><span class="c14 c30">=5<br></span><span
            class="c14 c21">IP_BROKER</span><span class="c14 c30">=127.0.0.1<br></span><span
            class="c14 c21">PUERTO_BROKER</span><span class="c14 c30">=5002<br></span><span
            class="c14 c21">LOG_FILE</span><span class="c36 c14 c30">=/home/utnso/log_team2.txt</span></p>
    <hr style="page-break-before:always;display:none;">
    <p class="c2 c24"><span class="c3"></span></p>
    <h1 class="c20 c17" id="h.4k668n3"><span>Proceso Game Boy</span></h1>
    <p class="c2"><span class="c3">Este proceso cumplira la funcion de ser un cliente que permita:</span></p>
    <ol class="c32 lst-kix_list_5-0 start" start="1">
        <li class="c25 c17"><span>Enviar un mensaje al Broker, a un Proceso Team o a un Proceso Game Card. </span></li>
        <li class="c2 c47"><span>Suscribirse a una cola de mensajes espec&iacute;fica del Broker por un tiempo
                limitado.</span></li>
    </ol>
    <p class="c2"><span class="c3">Para esto se iniciar&aacute; el proceso desde consola enviando los argumentos
            necesarios para poder enviar el mensaje al proceso destino.</span></p>
    <h2 class="c16" id="h.2zbgiuw"><span class="c31">Lineamiento e Implementaci&oacute;n</span></h2>
    <p class="c2"><span>El objetivo del proceso </span><span>Game Boy</span><span class="c3">&nbsp;es poder probar
            independientemente todos los otros procesos. De esta manera, el mismo podr&aacute; enviar cualquier mensaje
            a cualquier cola que el proceso Broker conozca y enviar por socket al proceso Team el mensaje de
            aparici&oacute;n de un nuevo Pokemon.</span></p>
    <p class="c2"><span>Este proceso no espera ninguna l&oacute;gica espec&iacute;fica o particular, solo
        </span><span>serializar&aacute;</span><span>&nbsp;y des </span><span>serializar&aacute;</span><span
            class="c3">&nbsp;los mensajes requeridos por argumentos y lo enviar&aacute; al proceso. Este proceso se
            ejecutar&aacute; enviando parametros por argumento que indicara cu&aacute;l ser&aacute; la funcionalidad que
            el mismo cumpla. Para esto, tendr&aacute; dos posibles variantes dependiendo si es para enviar un mensaje o
            suscribirse.</span></p>
    <p class="c2"><span class="c3">De esta manera, para el env&iacute;o de mensajes el formato de ejecuci&oacute;n del
            mismo sea el siguiente:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy [PROCESO] [</span><span class="c14 c30">TIPO_MENSAJE</span><span
            class="c36 c14 c30">] [ARGUMENTOS]*</span></p>
    <p class="c2"><span>Cabe aclarar que dicho formato </span><span class="c4">NO es modificable</span><span
            class="c3">. No se permite la inclusi&oacute;n de ningun argumento mas al mismo. De esta manera, la
            c&aacute;tedra proveer&aacute; al momento de realizar las pruebas en las distintas instancias de
            evaluaci&oacute;n scripts que contengan la ejecuci&oacute;n de varios de dichos comandos.</span></p>
    <p class="c2"><span>Los mensajes a implementar son:</span></p>
    <h3 class="c38 c17" id="h.1egqt2p"><span class="c5">Broker - New Pokemon</span></h3>
    <p class="c2"><span class="c3">Permitir&aacute; enviar un mensaje al Broker a la cola de mensajes NEW_POKEMON. Para
            esto, el formato del mensaje ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy BROKER </span><span class="c14 c30">NEW_POKEMON</span><span
            class="c14 c30">&nbsp;[POKEMON] [POSX] [POSY] [CANTIDAD]</span></p>
    <h3 class="c38 c17" id="h.3ygebqi"><span class="c5">Broker - Appeared Pokemon</span></h3>
    <p class="c2"><span>Permitir&aacute; enviar un mensaje al Broker a la cola de mensajes
        </span><span>APPEARED_POKEMON</span><span class="c3">. Para esto, el formato del mensaje ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy BROKER </span><span class="c14 c30">APPEARED_POKEMON</span><span
            class="c14 c30">&nbsp;[POKEMON] [POSX] [POSY] [</span><span
            class="c14 c30">ID_MENSAJE_CORRELATIVO</span><span class="c36 c14 c30">]</span></p>
    <p class="c2"><span>Cabe aclarar que el </span><span>ID_MENSAJE</span><span class="c3">&nbsp;ser&aacute; un valor
            definido tanto por la c&aacute;tedra como por los alumnos al realizar sus propios test. Este ID dentro de un
            script o entorno de ejecuci&oacute;n deber&aacute; ser &Uacute;NICO.</span></p>
    <h3 class="c38 c17" id="h.2dlolyb"><span class="c5">Broker - Catch Pokemon</span></h3>
    <p class="c2"><span>Permitir&aacute; enviar un mensaje al Broker a la cola de mensajes
        </span><span>CATCH_POKEMON</span><span class="c3">. Para esto, el formato del mensaje ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy BROKER </span><span class="c14 c30">CATCH_POKEMON</span><span
            class="c14 c30">&nbsp;[POKEMON] [POSX] [POSY]</span></p>
    <h3 class="c38 c17" id="h.sqyw64"><span class="c5">Broker - Caught Pokemon</span></h3>
    <p class="c2"><span>Permitir&aacute; enviar un mensaje al Broker a la cola de mensajes </span><span
            class="c14 c30">CAUGHT_POKEMON</span><span class="c3">. Para esto, el formato del mensaje
            ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy BROKER </span><span class="c14 c30">CAUGHT_POKEMON</span><span
            class="c14 c30">&nbsp;[</span><span class="c14 c30">ID_MENSAJE_CORRELATIVO</span><span class="c14 c30">]
            [OK/FAIL]</span></p>
    <h3 class="c38 c17" id="h.3cqmetx"><span class="c5">Broker - Get Pokemon</span></h3>
    <p class="c2"><span class="c3">Permitir&aacute; enviar un mensaje al Broker a la cola de mensajes GET_POKEMON. Para
            esto, el formato del mensaje ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy BROKER </span><span class="c14 c30">GET_POKEMON</span><span
            class="c14 c30">&nbsp;[POKEMON]</span></p>
    <h3 class="c38 c17" id="h.1rvwp1q"><span class="c5">Team - Appeared Pokemon</span></h3>
    <p class="c2"><span>Permitir&aacute; enviar un mensaje al Team como si
        </span><span>&eacute;l</span><span>&nbsp;mismo viniera desde la cola
            &nbsp;</span><span>APPEARED_POKEMON</span><span>&nbsp;del Broker. Para esto, el formato del mensaje
            ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./</span><span class="c14 c30">gameboy</span><span class="c14 c30">&nbsp;TEAM </span><span
            class="c14 c30">APPEARED_POKEMON</span><span class="c14 c30">&nbsp;[POKEMON] [POSX] [POSY]</span></p>
    <h3 class="c38 c17" id="h.4bvk7pj"><span class="c5">Game Card - New Pokemon</span></h3>
    <p class="c2"><span>Permitir&aacute; enviar un mensaje al Game Card </span><span>como si &eacute;l mismo viniera
            desde la cola</span><span>&nbsp;</span><span>NEW_POKEMON</span><span>&nbsp;del Broker</span><span
            class="c3">. Para esto, el formato del mensaje ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy </span><span class="c14 c30">GAMECARD</span><span
            class="c14 c30">&nbsp;</span><span class="c14 c30">NEW_POKEMON</span><span class="c14 c30">&nbsp;[POKEMON]
            [POSX] [POSY] [CANTIDAD] </span><span class="c14 c30">[</span><span class="c14 c30">ID_MENSAJE</span><span
            class="c14 c30">]</span></p>
    <h3 class="c38 c17" id="h.2r0uhxc"><span class="c5">Game Card - Catch Pokemon</span></h3>
    <p class="c2"><span>Permitir&aacute; enviar un mensaje al Game Card </span><span>como si &eacute;l mismo viniera
            desde la cola</span><span>&nbsp;</span><span>CATCH_POKEMON</span><span>&nbsp;del Broker</span><span
            class="c3">. Para esto, el formato del mensaje ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy </span><span class="c14 c30">GAMECARD</span><span
            class="c14 c30">&nbsp;</span><span class="c14 c30">CATCH_POKEMON</span><span class="c14 c30">&nbsp;[POKEMON]
            [POSX] [POSY] </span><span class="c14 c30">[</span><span class="c14 c30">ID_MENSAJE</span><span
            class="c14 c30">]</span></p>
    <h3 class="c38 c17" id="h.1664s55"><span class="c5">Game Card - Get Pokemon</span></h3>
    <p class="c2"><span>Permitir&aacute; enviar un mensaje al Game Card </span><span>como si &eacute;l mismo viniera
            desde la cola</span><span>&nbsp;</span><span>GET_POKEMON</span><span>&nbsp;del Broker</span><span
            class="c3">. Para esto, el formato del mensaje ser&aacute;:</span></p>
    <p class="c2"><span class="c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span><span
            class="c14 c30">./gameboy </span><span class="c14 c30">GAMECARD</span><span
            class="c14 c30">&nbsp;</span><span class="c14 c30">GET_POKEMON</span><span class="c14 c30">&nbsp;[POKEMON]
        </span><span class="c14 c30">[</span><span class="c14 c30">ID_MENSAJE</span><span class="c14 c30">]</span></p>
    <h3 class="c38 c17" id="h.3q5sasy"><span class="c5">Modo Suscriptor</span></h3>
    <p class="c2"><span>En este modo, el proceso GameBoy deber&aacute; conectarse como suscriptor durante un tiempo
            definido en segundos pasado por par&aacute;metro. Para esto se mantendr&aacute; la siguiente nomenclatura en
            su ejecuci&oacute;n:</span></p>
    <p class="c2"><span class="c36 c14 c30">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;./gameboy SUSCRIPTOR
            [COLA_DE_MENSAJES] [TIEMPO]</span></p>
    <p class="c2"><span class="c3">Este modo permitir&aacute; obtener los mensajes actuales que contiene en memoria el
            Broker y probar efectiva y correctamente el algoritmo de reemplazo y la compactaci&oacute;n.</span></p>
    <h2 class="c16" id="h.25b2l0r"><span class="c31">Logs obligatorios</span></h2>
    <p class="c2"><span>Para permitir la verificaci&oacute;n/validaci&oacute;n del m&oacute;dulo se exigir&aacute; tener
            un archivo de log espec&iacute;fico e independiente que contenga la informaci&oacute;n indicada en esta
            secci&oacute;n. </span><span class="c4">No se permite la inclusi&oacute;n de otros mensajes y
            exclusi&oacute;n de ninguno de los mismos</span><span>&nbsp;(la falta o agregado de alguno puede implicar la
            desaprobaci&oacute;n del grupo). Dado que el log ser&aacute; el medio de validaci&oacute;n del trabajo
            pr&aacute;ctico </span><span class="c4">se exige no utilizar la consola como medio de logueo</span><span
            class="c3">. Cada operaci&oacute;n debe loguearse en una &uacute;nica l&iacute;nea indicando la misma y sus
            datos, en caso que el grupo desee loguear contenido extra deber&aacute; realizarlo en un archivo
            independiente.</span></p>
    <p class="c2"><span class="c3">Las acciones a loguear en este archivo son:</span></p>
    <ol class="c32 lst-kix_list_31-0 start" start="1">
        <li class="c25 c17"><span>Conexi&oacute;n a cualquier proceso.</span></li>
        <li class="c25 c17"><span>Suscripci&oacute;n a una cola de mensajes.</span></li>
        <li class="c25 c17"><span>Llegada de un nuevo mensaje a una cola de mensajes.</span></li>
    </ol>
    <h2 class="c16" id="h.kgcv8k"><span class="c31">Archivo de Configuraci&oacute;n</span></h2>
    <p class="c2"><span class="c3">El proceso deber&aacute; poseer un archivo de configuraci&oacute;n en una
            ubicaci&oacute;n conocida donde se deber&aacute;n especificar, al menos, los siguientes
            par&aacute;metros:</span></p><a id="t.4f0745e6609816e8d2788fd82e74ba8e4e3b642c"></a><a id="t.3"></a>
    <table class="c37">
        <tbody>
            <tr class="c10">
                <td class="c28 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Campo</span></p>
                </td>
                <td class="c28 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Tipo</span></p>
                </td>
                <td class="c28 c64" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">Ejemplo</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">IP_BROKER</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c36 c14 c78">127.0.0.1</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">IP_TEAM</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c36 c14 c78">127.0.0.2</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span>IP_GAMECARD</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[String]</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c36 c14 c78">127.0.0.3</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span>PUERTO_BROKER</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c36 c14 c78">5003</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span>PUERTO_TEAM</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c36 c14 c78">5002</span></p>
                </td>
            </tr>
            <tr class="c10">
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span>PUERTO_GAMECARD</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c3">[Num&eacute;rico]</span></p>
                </td>
                <td class="c28" colspan="1" rowspan="1">
                    <p class="c7"><span class="c36 c14 c78">5001</span></p>
                </td>
            </tr>
        </tbody>
    </table>
    <p class="c2 c24"><span class="c3"></span></p>
    <p class="c2"><span class="c3">Queda a decisi&oacute;n del grupo el agregado de m&aacute;s par&aacute;metros al
            mismo.</span></p>
    <h3 class="c38 c17" id="h.34g0dwd"><span class="c5">Ejemplo de Archivo de Configuraci&oacute;n</span></h3>
    <p class="c2 c58"><span class="c14 c27">IP_BROKER</span><span class="c14">=127.0.0.1<br></span><span
            class="c14 c27">IP_TEAM</span><span class="c14">=127.0.0.2<br></span><span
            class="c14 c27">IP_GAMECARD</span><span class="c14">=127.0.0.3<br></span><span
            class="c14 c27">PUERTO_BROKER</span><span class="c14">=5003<br></span><span
            class="c14 c27">PUERTO_TEAM</span><span class="c14">=5002<br></span><span
            class="c14 c27">PUERTO_GAMECARD</span><span class="c14">=5001</span></p>
    <h1 class="c20 c17" id="h.1jlao46"><span class="c67 c27 c40 c48">Anexo I - Ejemplos de Flujos</span></h1>
    <h2 class="c16" id="h.43ky6rz"><span>Flujo New Pokemon - Appeared Pokemon<br></span><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 603.51px; height: 283.83px;"><img
                alt="" src="images/image6.png"
                style="width: 603.51px; height: 283.83px; margin-left: 0.00px; margin-top: 0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></h2>
    <p class="c2"><span>El Game Boy va a ser nuestro punto de partida para crear un nuevo pokemon. Este le va a enviar
            un mensaje al Broker a trav&eacute;s de la cola </span><span>NEW_POKEMON</span><span>&nbsp;indicando el
        </span><span>pokemon</span><span>, su posici&oacute;n y su cantidad. El broker luego, le deber&aacute; informar
            a todos los procesos Game Card que est&eacute;n suscritos a la cola de mensajes. Los procesos Game Card
        </span><span>avisar&aacute;n</span><span>&nbsp;en la cola de mensajes de
        </span><span>APPEARED_POKEMON</span><span class="c3">&nbsp;que los pokemones fueron agregados correctamente.
            Nuevamente el proceso Broker va a notificar a todos los procesos suscritos a dicha cola del nuevo
            evento.</span></p>
    <h2 class="c16" id="h.2iq8gzs"><span class="c31">Flujo Get Pokemon - Localized Pokemon</span></h2>
    <p class="c2"><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 603.51px; height: 283.83px;"><img
                alt="" src="images/image5.png"
                style="width: 603.51px; height: 283.83px; margin-left: 0.00px; margin-top: 0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></p>
    <p class="c2"><span>Al iniciar el proceso Team, va a enviar un mensaje por cada pokemon que requiera capturar, a
            trav&eacute;s de la cola de GET_POKEMON. El Broker luego va a redirigir el mensaje a los procesos suscritos.
            Una vez que la Game Card recibe el mensaje, va a recopilar la informaci&oacute;n que tenga de ese pokemon
            (cantidad y posici&oacute;n) y va a enviarlos por la cola de </span><span>LOCALIZED_POKEMON</span><span>. El
            proceso </span><span>Game Boy</span><span class="c3">&nbsp;tambien podra enviar el mensaje de GET_POKEMON al
            Game Card. Este flujo nos permitir&aacute; la evaluaci&oacute;n del trabajo pr&aacute;ctico.</span></p>
    <h2 class="c16" id="h.xvir7l"><span class="c31">Flujo Catch Pokemon - Caught Pokemon</span></h2>
    <p class="c2"><span
            style="overflow: hidden; display: inline-block; margin: 0.00px 0.00px; border: 0.00px solid #000000; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px); width: 603.51px; height: 283.83px;"><img
                alt="" src="images/image7.png"
                style="width: 603.51px; height: 283.83px; margin-left: 0.00px; margin-top: 0.00px; transform: rotate(0.00rad) translateZ(0px); -webkit-transform: rotate(0.00rad) translateZ(0px);"
                title=""></span></p>
    <p class="c2"><span>Este flujo es iniciado por la aparici&oacute;n de nuevos pokemons (cuando el Team recibe un
            mensaje en APEARED_POKEMON). Una vez que los procesos se enteran que apareci&oacute; un nuevo pok&eacute;mon
            y determinaron si que lo necesitan, van a intentar capturarlo (utilizando el proceso explicado en el proceso
            Team). Para esto cada proceso Team va a enviar un mensaje a trav&eacute;s de la cola de
        </span><span>CATCH_POKEMON</span><span>&nbsp;al Boker, el cual va a reenviar a todos los procesos
        </span><span>subscriptos</span><span>&nbsp;a dicha cola, el mensaje. Una vez que el Game Card resuelva las
            peticiones, el Broker va a informar a todos los procesos teams todos los mensajes de
        </span><span>CAUGHT_POKEMON</span><span>, los cuales deber&aacute; ignorar todos los mensajes que no
            correspondan con su id. El proceso </span><span>Game Boy</span><span class="c3">&nbsp;tambien podra enviar
            el mensaje de CATCH_POKEMON y CAUGHT_POKEMON al Broker. Este deber&aacute; distribuir correctamente los
            nuevos mensajes a los suscriptores. Este flujo nos permitir&aacute; la evaluaci&oacute;n del trabajo
            pr&aacute;ctico.</span></p>
    <hr style="page-break-before:always;display:none;">
    <p class="c2 c24"><span class="c94 c4 c48 c78"></span></p>
    <h1 class="c17 c20" id="h.3hv69ve"><span class="c67 c27 c40 c48">Anexo II - Mensajes en memoria</span></h1>
    <p class="c2"><span class="c3">El objetivo de este anexo es definir con ejemplos c&oacute;mo se guardan los
            distintos tipos de mensaje en memoria. El objetivo de esto es normalizar el consumo de memoria principal
            para los distintos mensajes.</span></p>
    <h3 class="c38 c17" id="h.1x0gk37"><span class="c5">Tama&ntilde;o de New Pokemon</span></h3>
    <p class="c2"><span class="c3">Este mensaje tendr&aacute; el nombre del Pokemon a enviar, las coordenadas de la
            posici&oacute;n donde se encuentra y la cantidad de pok&eacute;mon de esta especie que habra en dicha
            posicion. Un ejemplo del mensaje es: </span></p>
    <p class="c2"><span class="c14 c30">&lsquo;Pikachu&rsquo; 5 10 2</span></p>
    <p class="c2"><span>Vi&eacute;ndolo a nivel tipo de dato vamos a tener un
        </span><span>uint_32</span><span>&nbsp;para saber el largo del nombre del pok&eacute;mon, m&aacute;s el nombre
            del pokemon y tres </span><span>uint_32</span><span>&nbsp;indicando la posici&oacute;n y la cantidad. Este
            ejemplo tendr&aacute; un tama&ntilde;o de 23 bytes en memoria principal (lo que ocupan cuatro
        </span><span>uint_32</span><span class="c3">&nbsp;m&aacute;s el largo del nombre del pokemon). </span></p>
    <h3 class="c17 c105" id="h.1gz2steedxyk"><span class="c43 c40 c73">Tama&ntilde;o de Localized
            Pokemon</span><span><br></span><span class="c33">Este mensaje tendr&aacute; el nombre del pok&eacute;mon, un
            entero para la cantidad de pares de coordenadas y los pares de coordenadas donde se encuentra el mismo. Un
            ejemplo del mensaje es: </span></h3>
    <p class="c2"><span class="c14 c30">&lsquo;Pikachu&rsquo; 3 4 5 1 5 9 3</span></p>
    <p class="c2"><span>Vi&eacute;ndolo a nivel tipo de dato vamos a tener un
        </span><span>uint_32</span><span>&nbsp;para saber el largo del nombre del pok&eacute;mon, el nombre del
        </span><span>pokemon</span><span>, un </span><span>uint_32</span><span>&nbsp;indicando la cantidad de posiciones
            donde se encuentra y un par de </span><span>uint_32</span><span>&nbsp;para cada posici&oacute;n donde se
            encuentre. Este ejemplo tendr&aacute; un tama&ntilde;o de 39 bytes en memoria principal (lo que ocupa un
        </span><span>uint_32</span><span>&nbsp;multiplicado por los 8 que tenemos m&aacute;s el largo del nombre del
            pokemon). </span></p>
    <h3 class="c38 c17" id="h.4h042r0"><span class="c5">Tama&ntilde;o de Get Pokemon</span></h3>
    <p class="c2"><span class="c3">Este mensaje tendr&aacute; el nombre del pokemon. Un ejemplo del mensaje es: </span>
    </p>
    <p class="c2"><span class="c36 c14 c30">&lsquo;Pikachu&rsquo;</span></p>
    <p class="c2"><span>Vi&eacute;ndolo a nivel tipo de dato vamos a tener un
        </span><span>uint_32</span><span>&nbsp;para saber el largo del nombre del pokemon y luego el nombre del pokemon.
            Este ejemplo tendr&aacute; un tama&ntilde;o de 11 bytes en memoria principal (lo que ocupa un
        </span><span>uint_32</span><span>&nbsp;m&aacute;s el largo del nombre del pokemon). </span></p>
    <h3 class="c38 c17" id="h.2w5ecyt"><span class="c5">Tama&ntilde;o de Appeared Pokemon</span></h3>
    <p class="c2"><span class="c3">Este mensaje tendr&aacute; el nombre del pokemon y para indicar la posici&oacute;n en
            X y en Y. Un ejemplo del mensaje es: </span></p>
    <p class="c2"><span class="c36 c14 c30">&lsquo;Pikachu&rsquo; 1 5</span></p>
    <p class="c2"><span>Vi&eacute;ndolo a nivel tipo de dato vamos a tener un
        </span><span>uint_32</span><span>&nbsp;para saber el largo del nombre del pok&eacute;mon, &nbsp;el nombre del
            pokemon y dos </span><span>uint_32</span><span>&nbsp;indicando la posici&oacute;n. Este ejemplo
            tendr&aacute; un tama&ntilde;o de 19 bytes en memoria principal (lo que ocupan tres
        </span><span>uint_32</span><span class="c3">&nbsp;m&aacute;s el largo del nombre del pokemon). </span></p>
    <h3 class="c38 c17" id="h.1baon6m"><span class="c5">Tama&ntilde;o de Catch Pokemon</span></h3>
    <p class="c2"><span class="c3">Este mensaje tendr&aacute; el nombre del pokemon y la posici&oacute;n en X y en Y. Un
            ejemplo del mensaje es: </span></p>
    <p class="c2"><span class="c36 c14 c30">&lsquo;Pikachu&rsquo; 1 5</span></p>
    <p class="c2"><span>Vi&eacute;ndolo a nivel tipo de dato vamos a tener un
        </span><span>uint_32</span><span>&nbsp;para saber el largo del nombre del pok&eacute;mon, el nombre del pokemon
            y luego dos </span><span>uint_32</span><span>&nbsp;indicando la posici&oacute;n. Este ejemplo va a tener un
            tama&ntilde;o de 19 bytes en memoria principal (lo que ocupan tres </span><span>uint_32</span><span
            class="c3">&nbsp;m&aacute;s el largo del nombre del pokemon). </span></p>
    <h3 class="c38 c17" id="h.3vac5uf"><span class="c5">Tama&ntilde;o de Caught Pokemon</span></h3>
    <p class="c2"><span>Este mensaje </span><span>tendr&aacute;</span><span class="c3">&nbsp;un valor para indicar si se
            pudo o no atrapar al pokemon (0 o 1). Un ejemplo del mensaje es: </span></p>
    <p class="c2"><span class="c36 c14 c30">0</span></p>
    <p class="c2"><span>Vi&eacute;ndolo a nivel tipo de dato vamos a tener un
        </span><span>uint_32</span><span>&nbsp;para saber si se puedo o no atrapar al pokemon. Este ejemplo va a tener
            un tama&ntilde;o de 4 bytes en memoria principal (lo que ocupa un </span><span>uint_32</span><span
            class="c3">). </span></p>
    <p class="c2 c24"><span class="c3"></span></p>
    <p class="c2 c24"><span class="c3"></span></p>
    <h1 class="c82 c17 c96" id="h.2afmg28"><span class="c27 c40 c48 c67"></span></h1>
    <p class="c2 c24"><span class="c67 c27 c40 c48"></span></p>
    <hr style="page-break-before:always;display:none;">
    <h1 class="c17 c82" id="h.pkwqa1"><span class="c67 c27 c40 c48">Descripci&oacute;n de las entregas</span></h1>
    <h2 class="c16 c72" id="h.39kk8xu"><span class="c31"></span></h2>
    <h2 class="c16" id="h.9vyywhatg0r2"><span class="c31">Hito 1: Conexi&oacute;n Inicial</span></h2><a
        id="t.168861aa012b7270a2b85e389460dcdc3ebff0bb"></a><a id="t.4"></a>
    <table class="c37">
        <tbody>
            <tr class="c10">
                <td class="c65" colspan="1" rowspan="1">
                    <p class="c62"><span class="c43 c40">Fecha</span><span class="c43">: 25/04</span></p>
                    <p class="c62"><span class="c43 c40">Objetivos</span><span class="c15">:</span></p>
                    <ul class="c32 lst-kix_list_38-0 start">
                        <li class="c80 c47"><span class="c18">Familiarizarse con Linux y su consola, el entorno de
                                desarrollo y el repositorio.</span></li>
                        <li class="c80 c47"><span class="c18">Aplicar las Commons Libraries, principalmente las
                                funciones para </span><span class="c18">listas</span><span class="c18">, archivos de
                                conf y logs</span></li>
                        <li class="c47 c75"><span class="c18">Definir el Protocolo de Comunicaci&oacute;n</span></li>
                    </ul>
                    <p class="c103"><span class="c43 c40">Implementaci&oacute;n m&iacute;nima</span><span
                            class="c43">:</span></p>
                    <ul class="c32 lst-kix_list_21-0 start">
                        <li class="c47 c109"><span class="c8">Una biblioteca muy b&aacute;sica que permita enviar
                                strings hasta un proceso que act&uacute;e de servidor.</span></li>
                    </ul>
                    <p class="c62"><span class="c18 c40">Lectura recomendada: </span></p>
                    <ul class="c32 lst-kix_list_6-0 start">
                        <li class="c9"><span class="c18">Tutorial de &ldquo;C&oacute;mo arrancar&rdquo; de la materia:
                            </span><span class="c45 c49 c18"><a class="c19"
                                    href="https://www.google.com/url?q=http://faq.utnso.com.ar/arrancar&amp;sa=D&amp;ust=1595200539718000&amp;usg=AOvVaw2qbCrNKHyyKY84hIrvnsKs">http://faq.utnso.com.ar/arrancar</a></span>
                        </li>
                        <li class="c9"><span class="c18">Beej Guide to Network Programming - </span><span
                                class="c45 c18 c114">&nbsp;</span><span class="c45 c49 c18"><a class="c19"
                                    href="https://www.google.com/url?q=https://beej.us/guide/bgnet/&amp;sa=D&amp;ust=1595200539718000&amp;usg=AOvVaw1PjSmHuZ2EQJrFFvW-jGL9">https://beej.us/guide/bgnet/</a></span>
                        </li>
                        <li class="c9"><span class="c18">SO UTN FRBA Commons Libraries - </span><span
                                class="c45 c49 c18"><a class="c19"
                                    href="https://www.google.com/url?q=https://github.com/sisoputnfrba/so-commons-library&amp;sa=D&amp;ust=1595200539718000&amp;usg=AOvVaw2_Ymc8J69tVsyRBO2l7ZxO">https://github.com/sisoputnfrba/so-commons-library</a></span><span
                                class="c18">&nbsp;</span></li>
                        <li class="c9"><span class="c18">Gu&iacute;a de Punteros en C - </span><span
                                class="c45 c18 c49"><a class="c19"
                                    href="https://www.google.com/url?q=http://faq.utnso.com.ar/punteros&amp;sa=D&amp;ust=1595200539719000&amp;usg=AOvVaw2tXUyYPHx6EJy72to3UX9c">http://faq.utnso.com.ar/punteros</a></span>
                        </li>
                    </ul>
                </td>
            </tr>
        </tbody>
    </table>
    <p class="c17 c24 c104"><span class="c3"></span></p>
    <h2 class="c16" id="h.1opuj5n"><span class="c31">Hito 2: Avance del Grupo</span></h2><a
        id="t.86d006e3825ec5cd9e7ddaaed73f31d4eed0705e"></a><a id="t.5"></a>
    <table class="c37">
        <tbody>
            <tr class="c10">
                <td class="c65" colspan="1" rowspan="1">
                    <p class="c62"><span class="c43 c40 c48">Fecha</span><span class="c43 c48 c79">: 16/05</span></p>
                    <p class="c75"><span class="c43 c40">Objetivos</span><span class="c15">:</span></p>
                    <ul class="c32 lst-kix_list_22-0 start">
                        <li class="c80 c47"><span class="c18 c40">Proceso Team</span><span class="c18">: Permitir
                                solamente planificar de forma FIFO un conjunto de entrenadores.</span></li>
                        <li class="c80 c47"><span class="c18 c40">Proceso Broker</span><span class="c18">:
                                Implementaci&oacute;n completa de la administraci&oacute;n de las colas de mensajes.
                                Aceptar suscripciones a una cola de mensajes espec&iacute;fica.</span></li>
                        <li class="c75 c47"><span class="c18 c40">Proceso GameBoy</span><span class="c18">: Permitir el
                                env&iacute;o de varios mensajes al proceso Broker y el mensaje Appeared Pokemon al
                                proceso Team.</span></li>
                    </ul>
                    <p class="c75"><span class="c18 c40">Lectura recomendada: </span></p>
                    <ul class="c32 lst-kix_list_1-0 start">
                        <li class="c9"><span class="c8">Sistemas Operativos, Silberschatz, Galvin - Cap&iacute;tulo 3:
                                Procesos y Cap&iacute;tulo 4: Hilos</span></li>
                        <li class="c9"><span class="c18">Sistemas Operativos, Stallings, William - Parte IV:
                                Planificaci&oacute;n</span></li>
                    </ul>
                </td>
            </tr>
        </tbody>
    </table>
    <h2 class="c17 c72 c74" id="h.48pi1tg"><span class="c31"></span></h2>
    <hr style="page-break-before:always;display:none;">
    <h2 class="c16 c72" id="h.2nusc19"><span class="c31"></span></h2>
    <h2 class="c16" id="h.1302m92"><span class="c31">Hito 3: Checkpoint &ldquo;Presencial&rdquo; - V&iacute;a pantalla
            compartida</span></h2><a id="t.c52278e7535b97dbfd6a3ce298741cdac29a56ee"></a><a id="t.6"></a>
    <table class="c37">
        <tbody>
            <tr class="c10">
                <td class="c65" colspan="1" rowspan="1">
                    <p class="c62"><span class="c43 c40 c48">Fecha</span><span class="c43 c48 c79">: </span><span
                            class="c43">13</span><span class="c43 c48 c79">/06</span><span class="c15">&nbsp;</span></p>
                    <p class="c80"><span class="c43 c40">Objetivos</span><span class="c15">:</span></p>
                    <ul class="c32 lst-kix_list_34-0 start">
                        <li class="c80 c47"><span class="c18 c40">Proceso Team</span><span class="c18">: Permitir el
                                env&iacute;o de mensajes al Broker para Catch Pokemon y Get Pokemon.</span></li>
                        <li class="c80 c47"><span class="c18 c40">Proceso Broker</span><span class="c18">:
                                Implementaci&oacute;n del sistema de Particiones Din&aacute;micas. Administrar flujo de
                                mensajes y env&iacute;o de los mismos a los distintos suscriptores.</span></li>
                        <li class="c80 c47"><span class="c18 c40">Proceso GameCard</span><span class="c18">: Comenzar
                                implementaci&oacute;n de Tall Grass. Creaci&oacute;n de archivos y directorios.</span>
                        </li>
                        <li class="c75 c47"><span class="c18 c40">Proceso GameBoy</span><span class="c18">: Finalizar el
                                desarrollo del m&oacute;dulo.</span></li>
                    </ul>
                    <p class="c100"><span class="c18 c40">Lectura recomendada: </span></p>
                    <ul class="c32 lst-kix_list_6-0">
                        <li class="c9"><span class="c8">Sistemas Operativos, Silberschatz, Galvin 7ma Ed. -
                                Cap&iacute;tulo 6: Sincronizaci&oacute;n de Procesos</span></li>
                        <li class="c9"><span class="c8">Sistemas Operativos, Stallings, William - Cap&iacute;tulo 5:
                                Concurrencia</span></li>
                        <li class="c9"><span class="c8">Sistemas Operativos, Silberschatz, Galvin 7ma Ed. -
                                Cap&iacute;tulo 8: Memoria Principal</span></li>
                        <li class="c9"><span class="c18">Sistemas Operativos, Stallings, William - </span><span
                                class="c18">Cap&iacute;tulo</span><span class="c18">&nbsp;7: </span><span
                                class="c18">Gesti&oacute;n</span><span class="c18">&nbsp;de la Memoria</span></li>
                        <li class="c9"><span class="c8">Sistemas Operativos, Silberschatz, Galvin 7ma Ed. -
                                Cap&iacute;tulo 10: Interfaz del Sistema de Archivos</span></li>
                        <li class="c9"><span class="c8">Sistemas Operativos, Stallings, William - Cap&iacute;tulo 12:
                                Gesti&oacute;n de Ficheros</span></li>
                    </ul>
                </td>
            </tr>
        </tbody>
    </table>
    <h2 class="c74 c17" id="h.3mzq4wv"><span class="c90 c40 c48 c101">&nbsp;</span></h2>
    <h2 class="c16" id="h.2250f4o"><span class="c31">Hito 4: Avance del Grupo</span></h2><a
        id="t.2ca7c4bcb8be3bb4a00e13b92a112f31eadd46e2"></a><a id="t.7"></a>
    <table class="c37">
        <tbody>
            <tr class="c10">
                <td class="c65" colspan="1" rowspan="1">
                    <p class="c62"><span class="c40 c43">Fechas</span><span class="c43">: 27/06</span></p>
                    <p class="c80"><span class="c43 c40">Objetivos</span><span class="c15">:</span></p>
                    <ul class="c32 lst-kix_list_12-0 start">
                        <li class="c80 c47"><span class="c18 c40">Proceso Team</span><span class="c8">:
                                Implementaci&oacute;n del algoritmo RR, desarrollo de m&eacute;tricas.</span></li>
                        <li class="c80 c47"><span class="c18 c40">Proceso Broker</span><span class="c8">: Sistema de
                                reemplazo y compactaci&oacute;n.</span></li>
                        <li class="c75 c47"><span class="c18 c40">Proceso GameCard</span><span class="c8">: Avances
                                sobre la implementaci&oacute;n del FileSystem de Tall Grass. Poder leer y escribir
                                archivos.</span></li>
                    </ul>
                    <p class="c108"><span class="c18 c40">Lectura recomendada:</span></p>
                    <ul class="c32 lst-kix_list_6-0">
                        <li class="c9"><span class="c18">Sistemas Operativos, Silberschatz, Galvin 7ma Ed. -
                                Cap&iacute;tulo 11: Implementaci&oacute;n de Sistemas de Archivos</span></li>
                    </ul>
                </td>
            </tr>
        </tbody>
    </table>
    <p class="c2"><span class="c36 c48 c79 c90">&nbsp;</span></p>
    <h2 class="c16" id="h.haapch"><span class="c31">Hito 5: Entregas Finales</span></h2><a
        id="t.2e74acb0bc417d5277b7aef3039fc617d567cccf"></a><a id="t.8"></a>
    <table class="c37">
        <tbody>
            <tr class="c10">
                <td class="c65" colspan="1" rowspan="1">
                    <p class="c62"><span class="c43 c40 c48">Fechas</span><span class="c43 c48 c79">: </span><span
                            class="c43">18</span><span class="c43 c48 c79">/7 - </span><span class="c43">25</span><span
                            class="c43 c48 c79">/</span><span class="c43">7</span><span class="c43 c48 c79">&nbsp;-
                        </span><span class="c43">8</span><span class="c43 c48 c79">/8</span><span
                            class="c43"><br></span></p>
                    <p class="c80"><span class="c43 c40">Objetivos</span><span class="c15">:</span></p>
                    <ul class="c32 lst-kix_list_28-0 start">
                        <li class="c59 c47"><span class="c18">Probar el TP en un entorno distribuido</span></li>
                        <li class="c59 c47"><span class="c18">Realizar pruebas intensivas</span></li>
                        <li class="c47 c59"><span class="c18">Finalizar el desarrollo de todos los procesos</span></li>
                        <li class="c80 c47"><span class="c18">Todos los componentes del TP ejecutan los requerimientos
                                de forma integral, bajo escenarios de stress.</span></li>
                    </ul>
                    <p class="c62"><span class="c18 c40">Lectura recomendada:</span></p>
                    <ul class="c32 lst-kix_list_6-0">
                        <li class="c23"><span class="c18">Gu&iacute;as de Debugging del Blog utnso.com &nbsp;-
                            </span><span class="c45 c49 c18"><a class="c19"
                                    href="https://www.google.com/url?q=https://www.utnso.com.ar/recursos/guias/&amp;sa=D&amp;ust=1595200539728000&amp;usg=AOvVaw3Ho47F70PGAJPY5VLJiBuO">https://www.utnso.com.ar/recursos/guias/</a></span><span
                                class="c18">&nbsp;</span></li>
                        <li class="c23"><span class="c18">MarioBash: Tutorial para aprender a usar la consola &nbsp;-
                            </span><span class="c45 c49 c18"><a class="c19"
                                    href="https://www.google.com/url?q=http://faq.utnso.com.ar/mariobash&amp;sa=D&amp;ust=1595200539728000&amp;usg=AOvVaw27Ne4OPyUB7lthfP8RBVzA">http://faq.utnso.com.ar/mariobash</a></span>
                        </li>
                        <li class="c23"><span class="c18">Tutoral de como desplegar un proyecto</span><span
                                class="c18 c40">&nbsp;- &nbsp;</span><span class="c45 c49 c18"><a class="c19"
                                    href="https://www.google.com/url?q=https://github.com/sisoputnfrba/so-deploy&amp;sa=D&amp;ust=1595200539729000&amp;usg=AOvVaw3AKHjoUeaHRFqetb-jUbWP">https://github.com/sisoputnfrba/so-deploy</a></span>
                        </li>
                    </ul>
                </td>
            </tr>
        </tbody>
    </table>
    <p class="c2 c24"><span class="c67 c48 c79 c113"></span></p>
    <div>
        <p class="c17 c53"><span class="c18">P&aacute;gina </span><span class="c18">/</span></p>
    </div>
    <hr class="c98">
    <div>
        <p class="c71 c17"><a href="#ftnt_ref1" id="ftnt1">[1]</a><span class="c36 c48 c30 c79">&nbsp;Referencias
                bibliogr&aacute;ficas: secci&oacute;n 7.2, cap. 7, Stallings 6&deg; ed.; secci&oacute;n 8.3.2/3, cap. 8,
                Silberschatz 7&deg; ed.</span></p>
    </div>
    <div>
        <p class="c71 c17"><a href="#ftnt_ref2" id="ftnt2">[2]</a><span class="c30">&nbsp;Se deber&aacute; poder
                configurar la frecuencia de compactaci&oacute;n (en la unidad &ldquo;cantidad de b&uacute;squedas
                fallidas&rdquo;). El valor </span><span class="c30">-1</span><span
                class="c36 c48 c30 c79">&nbsp;indicar&aacute; compactar solamente cuando se hayan eliminado todas las
                particiones.</span></p>
    </div>
    <div>
        <p class="c71 c17"><a href="#ftnt_ref3" id="ftnt3">[3]</a><span class="c36 c48 c30 c79">&nbsp;Referencias
                bibliogr&aacute;ficas: secci&oacute;n 7.2, cap. 7, Stallings 6&deg; ed.;.</span></p>
    </div>
    <div>
        <p class="c69 c17"><a href="#ftnt_ref4" id="ftnt4">[4]</a><span class="c36 c48 c30 c79">&nbsp;Se recomienda
                investigar sobre el manejo de los bitarray de las commons library.</span></p>
    </div>
</body>

</html>

