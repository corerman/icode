<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>CorerMan 文件列表</title>
<link rel="stylesheet" type="text/css" href="css/SimpleTree.css"/>
<script type="text/javascript" src="js/jquery-1.6.min.js"></script>
<script type="text/javascript" src="js/SimpleTree.js"></script>
<script type="text/javascript">
$(function(){
	$(".st_tree").SimpleTree();
});
</script>
</head>
<body style="background: #f5f5f5 url(./css/grid.png);">
<div class="st_tree" style="width:400px; ">
	<?php
		print "<ul>";
		Scan('./',1); //传送扫描根目录 与 递归初始层数 这两个参数
		print "</ul>";	
	?>
		<?php
			function Scan($way,$level)
			{
				$list=scandir($way); //获取当前路径的文件列表，包括目录
				for($i=0;$i<count($list);$i++)
				{
					if($list[$i]!='.' && $list[$i]!='..' &&$list[$i]!="index.php"&&$list[$i]!="judge"&&$list[$i]!="css"&&$list[$i]!="js")
					{
						if(is_dir($way.$list[$i]."/")) //如果为目录 
						{							
							print "  <li>$list[$i]</li>\n";
								print "<ul    ";
								if($level<=1) // 每个文件夹只展开两层
										print "show=true";
								print ">\n";
							Scan($way.$list[$i]."/",$level+1); //递归进入下一层
							print "\n</ul>\n";
						}
						else
						{
							print "<li><a href=\"$way$list[$i]\">$list[$i]</a></li>\n";
						}		
					}	
				}
			}
		?>
</div>
</body>
</html>
