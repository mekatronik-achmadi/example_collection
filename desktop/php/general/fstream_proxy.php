#!/usr/bin/php
<?php

$auth = base64_encode('achmadi10@mhs.ep.its.ac.id:mekatro05');

// $aContext = array(
//     'http' => array(
// // 	'header' => "User-Agent:MyAgent/1.0\r\n",
// // 	'header' => "User-Agent:Mozilla/5.0\r\n",
//         'proxy' => 'tcp://10.100.1.15:8080',
//         'request_fulluri' => true,
//         'header' => "Proxy-Authorization: Basic $auth",
//         'timeout' => 60,
//     ),
// );

$aContext = array(
    'http' => array (
        'method'=>'GET',
        'proxy'=>'tcp://10.100.1.15:8080',
        'request_fulluri' => true,
        'header'=> array("Proxy-Authorization: Basic $auth", "Authorization: Basic $auth")

    ),
    'https' => array (
        'method'=>'GET',
        'proxy'=>'tcp://10.100.1.15:8080',
        'request_fulluri' => true,
        'header'=> array("Proxy-Authorization: Basic $auth", "Authorization: Basic $auth")
    )
); 

$cxContext = stream_context_create($aContext);

$sFile = file_get_contents("https://www.google.com/", False, $cxContext);
// $sFile = file_get_contents("https://www.facebook.com/", False, $cxContext);
// $sFile = file_get_contents("https://github.com/dtompkins/fbcmd/zipball/master", False, $cxContext);
echo $sFile;

// $w = stream_get_wrappers();
// echo 'openssl: ',  extension_loaded  ('openssl') ? 'yes':'no', "\n";
// echo 'http wrapper: ', in_array('http', $w) ? 'yes':'no', "\n";
// echo 'https wrapper: ', in_array('https', $w) ? 'yes':'no', "\n";
// echo 'wrappers: ', var_dump($w);

?> 
