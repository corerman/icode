<html>
	<head>
		<meta charset="utf-8" />
	</head>
	<body>
	<?php //包含函数代码库
	include('./weixin_function/weixin_function_event.php');
	include('./weixin_function/weixin_function_text.php');
	include('./weixin_function/weixin_function_image.php');
	include('./weixin_function/weixin_function_voice.php');
	include('./weixin_function/weixin_function_location.php');
	include('./weixin_function/weixin_function_link.php');
	?>
	
	
	<?php
	func_event($a);
	define("TOKEN", "weixin");
	$wechatObj = new wechatCallbackapiTest();
	if (isset($_GET['echostr'])) {
		$wechatObj->valid();
	}else{
		$wechatObj->responseMsg();
	}

	class wechatCallbackapiTest
	{
		public function valid()
		{
			$echoStr = $_GET["echostr"];
			if($this->checkSignature()){
				echo $echoStr;
				exit;
			}
		}

		private function checkSignature()  //检验通信标识
		{
			$signature = $_GET["signature"];
			$timestamp = $_GET["timestamp"];
			$nonce = $_GET["nonce"];

			$token = TOKEN;
			$tmpArr = array($token, $timestamp, $nonce);
			sort($tmpArr);
			$tmpStr = implode( $tmpArr );
			$tmpStr = sha1( $tmpStr );

			if( $tmpStr == $signature ){
				return true;
			}else{
				return false;
			}
		}

		public function responseMsg()
		{
			$postStr = $GLOBALS["HTTP_RAW_POST_DATA"]; //获取微信传送的数据
			
			if (!empty($postStr))
			{ //把数据转换到postStr类中
				$postObj = simplexml_load_string($postStr, 'SimpleXMLElement', LIBXML_NOCDATA); 
				$msgType=$postObj->MsgType; //获取事件类别
				
				//利用Switch筛选信息类别
				switch($msgType)  //传进去的参数是postObj对象
				{
					case 'event' :
						 func_event($postObj);
						 break;
					case 'text' :
						func_text($postObj);
						break;
					case 'image' :
						func_image($postObj);
						break;
					case 'voice' :
						func_voice($postObj);
						break;
					case 'location':
						func_location($postObj);
						break;
					case 'link' :
						func_link($postObj);
						break;
				}
				
			}
		}
	}
	?>

	</body>
</html>