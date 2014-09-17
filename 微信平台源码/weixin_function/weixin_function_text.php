<?php
	function func_text($postObj){
		//定义回复信息XML信息
		$reply_text="<xml>
					<ToUserName><![CDATA[%s]]></ToUserName>
					<FromUserName><![CDATA[%s]]></FromUserName>
					<CreateTime>%s</CreateTime>
					<MsgType><![CDATA[%s]]></MsgType>
					<Content><![CDATA[%s]]></Content>
					</xml>";
					
		$toUserName=$postObj->ToUserName;
		$fromUserName=$postObj->FromUserName;
		$createTime=time();
		$msgType="text";
		$menu=$postObj->Content; //获取页码
		/*对command进行分类
		0 公告
		1 我的题库 11北大题库
		*/
		$menu_level1=substr($menu,0,1); //获取菜单代码的第一个字母
		switch ($menu_level1){
			case '0' : //公告处理
				$content="公告栏：\n暂时为空！\n";
				$reply=sprintf($reply_text,$fromUserName,$toUserName,$createTime,$msgType,$content);
				echo $reply;
				break;
				
			case '1': //题库初步菜单
					if(strlen($menu)<=2) //根据用户输入的菜单长度
					{
						$content="尊敬的用户:\n  欢迎使用算法题库。\n\n题库菜单：\n  11: [北大ACM题库]\n\n";
						$content.="操作说明:\n";
						$content.="例如你需要选择北大题库，则输入: 11*** , ";
						$content.="***代表题目列表的页数。\n例如：11000代表 北大题库第0页。\n北大题库最大页码为305。";
						$reply=sprintf($reply_text,$fromUserName,$toUserName,$createTime,$msgType,$content);
						echo $reply;
					}
					else{
						$menu_level2=substr($menu,1,1);
						/*根据第二个字母选择题库平台
							1 北大题库
						 */
						 switch ($menu_level2)
						 {	
							case '1': //如果是北大库，利用poj_links函数处理
								$page_links=poj_links($menu);	
								$reply=sprintf($reply_text,$fromUserName,$toUserName,$createTime,$msgType,$page_links);
								echo $reply;
								break;
						 }	
					}
					break;
					
			case 2: //微信工具箱初步菜单	
				if(strlen($menu)<=2) //根据用户输入的菜单长度
					{
						$content="尊敬的用户:\n  欢迎使用工具箱。\n\n工具菜单：\n  21: [搜索百度云资源]\n\n";
						$content.="操作说明:\n";
						$content.="1. [搜索云资源]\n例如：你需要搜索百度云盘资源，则输入: 21*** , ";
						$content.="***代表搜索的关键字。\n例如：21 CS 1.6代表 搜索关键字为CS 1.6的网络资源。";
						$reply=sprintf($reply_text,$fromUserName,$toUserName,$createTime,$msgType,$content);
						echo $reply;
					}
				else{
						$menu_level2=substr($menu,1,1); //选择网盘
						switch ($menu_level2)
						{   //1代表百度网盘搜索
							case '1':
								$result="      < 搜索结果如下 >\n"; //记录抠取的信息
								$keyword=substr($menu,2);
								$keyword=trim($keyword);
								$keyword=str_replace(' ','+',$keyword);
								for($i=1;$i<=3;$i++)
								{
									//$result.=search_pan_from_google("173.194.72.31","pan.baidu.com",$i,$keyword,'/http:\/\/pan.baidu.com\/s\/\w{6,8}\"/');
									
									$result.=search_from_soso(urlencode($keyword),$i);//SoSo接口
								}
								alert($postObj,$result);
							break;
								
						}
					}
				break;
			default: //对于没有的菜单输入
				alert($postObj,"尊敬的用户:\n  您好，这里是Corer信息中心。\n操作菜单:\n  0: [最新公告]\n  1: [算法题库]\n  2: [超强工具箱]");
				break;
		}
		
		
		
	}
?>


<?php 
			function poj_links($string_pagenum){
				$pagenum=$string_pagenum;
				$pagenum=substr($pagenum,2); //抠取出页码
				if((int)$pagenum>305)
				{
					$result="警告:\n  北大ACM题库最大页码数为305！";
					return $result;
				}
				$volume_id=(int)$pagenum/10+1; //构造北大ACM卷数
				$link_way="http://poj.org/problemlist?volume=";
				$link_way.=(int)$volume_id; //构造卷数的链接地址
				$web_content=file($link_way);
				$result="序号   题目名称   通过率\n";
				$id=0;
				$start_id=((int)$pagenum%10);
				$start_id=10+$start_id*10;
				for($i=$start_id;$i<$start_id+10;$i++){
					$head=substr($web_content[$i],21,1);
					$id++;
					if($head>='1'&&$head<='4')
					{
					
						$point=stripos($web_content[$i],'(');
						$web_content[$i]=substr($web_content[$i],0,$point);
						$point =stripos($web_content[$i],'<td>');
						$web_content[$i]=substr($web_content[$i],$point+4);
						$web_content[$i]=str_replace("</td><td align=left>","",$web_content[$i]);
						$web_content[$i]=str_replace("lang=\"en-US\"","",$web_content[$i]);
						$web_content[$i]=str_replace("</td><td>"," ",$web_content[$i]);
						$web_content[$i]=str_replace("<a  href="," <a  href=\"http://poj.org/",$web_content[$i]);
						$web_content[$i]=str_replace(">","\">",$web_content[$i]);
						$web_content[$i]=str_replace("/a\"","/a",$web_content[$i]);
						$web_content[$i]=substr($web_content[$i],4);
						$result.=($id.$web_content[$i]."\n");
					}
				}
			return $result;		
			}	
?>

<?php
	function alert($postObj,$str_news){
	//单纯的输出文字的
		$reply_text="<xml>
					<ToUserName><![CDATA[%s]]></ToUserName>
					<FromUserName><![CDATA[%s]]></FromUserName>
					<CreateTime>%s</CreateTime>
					<MsgType><![CDATA[%s]]></MsgType>
					<Content><![CDATA[%s]]></Content>
					</xml>";
					
		$toUserName=$postObj->ToUserName;
		$fromUserName=$postObj->FromUserName;
		$createTime=time();
		$msgType="text";
		$content=$str_news;
		$reply=sprintf($reply_text,$fromUserName,$toUserName,$createTime,$msgType,$content);
		echo $reply;
	}
?>

<?php
	//封装谷歌检索信息函数
	function search_pan_from_google($google_ip,$str_pan_common_link,$pagenum,$key,$str_reg) //最后一个是正则字符串
		{
			$pagestart=$pagenum*10;
			$search_link="http://$google_ip/custom?hl=zh-CN&sitesearch=$str_pan_common_link&start=$pagestart&q=$key";
			$web_content=file($search_link);
			$line_count=count($web_content);
			$result="";
			for($i=0;$i<$line_count;$i++)
				if(strpos($web_content[$i],'pan.baidu.com'))
					$result.=$web_content[$i];
			$select_result; //存储结果的二维数组
			$count=preg_match_all($str_reg,$result,$select_result);
			$result="";
			for($i=0;$i<$count;$i++)
			{
				$select_result[0][$i]=substr($select_result[0][$i],0,strlen($select_result[0][$i])-1);
				$result.=("● [ <a href=\"".$select_result[0][$i]."\" target=\"_blank\">".$select_result[0][$i]."</a> ]\n");
			}
			return $result;
		}	
?>

<?php
	//借助SOSO平台进行搜索
	function search_from_soso($keyword,$pagenum){
		$str_link="http://www.soso.com/q?w=site%3Apan.baidu.com $keyword&pg=$pagenum"; //构造连接地址
		//利用curl读取数据
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL,$str_link);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
		curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);
		$web_content = curl_exec($ch);
		$result="";
		$select_result;
		$count;
		$count=preg_match_all('/http:\/\/pan.baidu.com\/s\/\w{6,8}\"\>/',$web_content,$select_result);
		//print $count;
		for($i=0;$i<$count;$i++)
		{
			$select_result[0][$i]=substr($select_result[0][$i],0,strlen($select_result[0][$i])-2);


			$result.=("● [ <a href=\"".$select_result[0][$i]."\" target=\"_blank\">".$select_result[0][$i]."</a> ]\n");
		}
		curl_close($ch);
		return $result;
	}
?>