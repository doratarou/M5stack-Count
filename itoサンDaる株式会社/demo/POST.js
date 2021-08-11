var http = require('http');
const fs = require('fs');


// var html = require('fs').readFileSync('/Users/user/Documents/itoサンDaる株式会社/home/商品一覧/商品詳細/thank-you.html');

 
http.createServer(function(req, res) {
 
  if(req.method === 'GET') {
    res.writeHead(200, {'Content-Type' : 'text/html'});
    res.end("a");
  } else if(req.method === 'POST') {
 
 
    //ここにPOST受信処理を記述する
    var data = '';
    var data2;

   //POSTデータを受けとる
   req.on('data', function(chunk) {data += chunk})
      .on('end', function() {
        data2= decodeURI(data);
        
        data2= data2.split("many=");
        data2=data2.pop();
        // data2=data2.str.replace("&","");
        data2=data2.replace("color=","");
        data2=data2.replace("type=","");
        data2=data2.split("&");
        //data2はリスト、個数、色、名前、の順に入っている
        fs.appendFile('data.txt', `[${data2[2]}]の[${data2[1]}]色を[${data2[0]}]個注文が入りました!!\n`, (err) => {
          if (err) throw err;
          console.log('test.txtに追記されました');
      });
        
        console.log(data2);
        res.end("b");

 
      })

}
 
}).listen(3000);
