<?php
 	function func_event($postObj){ 
	
		//定义回复信息XML信息
		$reply_text="<xml>
					<ToUserName><![CDATA[%s]]></ToUserName>
					<FromUserName><![CDATA[%s]]></FromUserName>
					<CreateTime>%s</CreateTime>
					<MsgType><![CDATA[%s]]></MsgType>
					<Content><![CDATA[%s]]></Content>
					</xml>";
		//定义菜单选项
		$command_number=array(" [最新通告]"," [算法题库]"," [超强工具箱]"); 
		
		$eventType=$postObj->Event;
		switch($eventType)
		{
			case 'subscribe' : //订阅事件
				//回复数组中的菜单信息
				$toUserName=$postObj->ToUserName;
				$fromUserName=$postObj->FromUserName;
				$createTime=time();
				$msgType="text";
				$content="  尊敬的用户：\n您好，这里是Corer信息中心。\n操作菜单：\n";
				$number=count($command_number); //对菜单数组进行计数
				print $command_number;
				for($i=0;$i<$number;$i++)
				{
					$content .= ("  ".$i .".".$command_number[$i]."\n");
				}
				//一定要注意下面的格式输入时formUserName与toUserName的顺序 是相反的，这符合逻辑。
				$reply=sprintf($reply_text,$fromUserName,$toUserName,$createTime,$msgType,$content);
				echo $reply;
				
		}
	
	
	}
?>