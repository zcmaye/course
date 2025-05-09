# Urllib

`urllib`是 Python 标准库中用于处理 URL 的模块，它提供了一系列用于处理 URL 的工具，能够实现从简单的 URL 读取到复杂的 HTTP 请求等操作。

urllib库提供了四大模块：

- **`urllib.request`**：用于打开和读取 URL，提供了高级的接口来处理不同类型的请求，像 HTTP、FTP 等协议的请求。
- **`urllib.error`**：包含了`urllib.request`抛出的异常，可用于捕获和处理请求过程中出现的错误。
- **`urllib.parse`**：用于解析和处理 URL，例如拆分 URL、合并 URL、编码和解码 URL 参数等。
- **`urllib.robotparser`**：用于解析网站的`robots.txt`文件，以此判断爬虫是否被允许访问该网站的特定页面，使用频率较少。

## urllib.parse

### 解析URL(`urlsplit`)

`urlparse`函数可以将一个 URL 拆分为多个组件，如协议、域名、路径、查询参数等。

```python
url = 'https://www.macrodef.com/path/to/resource?user_id=2&username=玩蛇#fragment'

parse_result = urllib.parse.urlsplit(url)

print(f"协议: {parse_result.scheme}")
print(f"域名: {parse_result.netloc}")
print(f"路径: {parse_result.path}")
print(f"查询参数: {parse_result.query}")
print(f"片段: {parse_result.fragment}")
```

在上述代码中，`urlparse`函数将 URL 拆分为各个组件，存储在`parsed_url`对象中，通过访问该对象的属性可以获取各个组件的值。

> 还有一个urlparser函数功能与urlsplit类似，只不过会多处理一个param，但是现代URL一定不会用到，所以不必使用urlparser！

### 合并 URL 组件 (`urlunsplit`)

`urlunparse`函数与`urlparse`相反，它可以将多个 URL 组件合并成一个完整的 URL。

```python
components = ['https','www.hdy.com','/path/to/resource','user_id=2&username=玩蛇','fragment']

url = urllib.parse.urlunsplit(components)

print(f'url {url}')
```

此代码中，将包含协议、域名、路径、查询参数和片段的元组传递给`urlunparse`函数，它会将这些组件合并成一个完整的 URL。

> 还有一个urlunparser函数功能与urlunsplit类似，只不过会多处理一个param，但是现代URL一定不会用到，所以不必使用urlunparser！

### 编解码URL参数

在浏览器中访问URL时，会发现浏览器把URL中的中文和一些字符转成了类似于`%E4%BD%A0`的编码，为什么呢？首先不是乱编码的，有一个编码叫做URL 编码（Percent-Encoding，也叫百分号编码），是为了 **让 URL 可以安全、正确地传输和解析**，主要解决以下几个问题：

##### 1. 为什么需要 URL 编码？

URL 只能使用 **有限字符集**（ASCII 字符），但实际使用中可能包含：

- **非 ASCII 字符**（如中文、日文、Emoji）
- **特殊字符**（如 `空格`、`?`、`#`、`&`、`=` 等，它们在 URL 中有特殊含义）
- **保留字符**（如 `/`, `:`, `@` 等，用于 URL 结构）

如果不编码，URL 可能会 **解析错误** 或 **传输失败**。

##### 2. URL 编码的规则

- **保留字符**（如 `?`, `=`, `/`, `#`）在特定位置有特殊含义，不能直接使用，否则会被解析成 URL 的结构部分。
- **非保留字符**（如字母 `A-Za-z`、数字 `0-9` 和 `-_.~`）**不需要编码**。
- **其他字符**（如空格、中文、`&`、`%`）必须转换成 `%` + **十六进制 ASCII 码**：
  - 空格 → `%20`（或者 `+`，但在查询参数里 `+` 会被解码成空格）
  - 中文 "你" → `%E4%BD%A0`（UTF-8 编码的十六进制表示）
  - `&` → `%26`（否则会被解析为参数分隔符）

在路径(path)、查询参数(query)、锚点(fragment)中，必须进行编码！

```css
#path
http://example.com/文件.pdf ❌（不能直接使用中文）
http://example.com/%E6%96%87%E4%BB%B6.pdf ✅（编码后）
#query
http://example.com/search?q=python&price=100 ❌（`&` 会被解析成分隔符）
http://example.com/search?q=python%26price%3D100 ✅（`&` → `%26`，`=` → `%3D`）
#fragment
http://example.com/page#章节1 ❌
http://example.com/page#%E7%AB%A0%E8%8A%821 ✅
```

##### 3. 编码(quote/quote_plus/urlencode)

###### quote

函数原型：

```python
def quote(string, safe='/', encoding=None, errors=None) -> str
```

- **用途**：对 **单个字符串** 进行 URL 编码（Percent-Encoding）。

- **特点**：

  - **默认不编码斜杠 `/`**（适用于路径部分）。
  - **空格** ``编码为`**%20**（不是 `+`）。
  - 适用于 **路径（Path）** 或 **Fragment（锚点）** 的编码。

- **示例:**

  ```python
  from urllib.parse import quote
  
  # 编码路径（保留 /）
  print(quote("文档/测试.pdf"))  
  # 输出: %E6%96%87%E6%A1%A3/%E6%B5%8B%E8%AF%95.pdf
  
  # 编码特殊字符
  print(quote("a b=c&d"))  
  # 输出: a%20b%3Dc%26d（空格→%20，=→%3D，&→%26）
  ```

###### quote_plus

函数原型:

```python
def quote_plus(string, safe='', encoding=None, errors=None) -> str
```

- **用途**：对 **查询参数（Query String）** 进行编码。

- **特点**：

  - **空格** `编码为 `**+**（符合 application/x-www-form-urlencoded` 标准）。
  - **`/` 也会被编码为 `%2F`**（除非手动设置 `safe='/'`）。
  - 适用于 **URL 查询参数（Query String）** 或 **POST 表单数据**。

- **示例：**

  ```python
  from urllib.parse import quote_plus
  
  # 编码查询参数（空格→+）
  print(quote_plus("a b=c&d"))  
  # 输出: a+b%3Dc%26d（空格→+，=→%3D，&→%26）
  
  # 对比 quote()
  print(quote("a b=c&d"))  
  # 输出: a%20b%3Dc%26d
  ```

###### urlencode

函数原型：

```python
def urlencode(query, doseq=False, safe='', encoding=None, errors=None,quote_via=quote_plus) -> str
```

- **用途**：将 **字典或键值对列表** 编码为 URL 查询字符串（`?key1=val1&key2=val2`）。

- **特点**：

  - 自动处理 **键和值** 的编码（相当于调用了 `quote_plus`）。
  - 支持嵌套数据（通过 `doseq=True` 处理列表值）。

- 示例：

  ```python
  from urllib.parse import urlencode
  
  # 字典 → 查询字符串
  params = {"q": "python 教程", "page": 1}
  print(urlencode(params))  
  # 输出: q=python+%E6%95%99%E7%A8%8B&page=1（空格→+，中文→%E6%95%99%E7%A8%8B）
  
  # 元组列表 → 查询字符串
  params_list = [("q", "python"), ("page", 1), ("sort", "newest")]
  print(urlencode(params_list))  
  # 输出: q=python&page=1&sort=newest
  
  # 处理多值（doseq=True）
  multi_params = {"q": ["python", "java"], "page": 1}
  print(urlencode(multi_params, doseq=True))  
  # 输出: q=python&q=java&page=1
  ```

###### 总结

- **`quote()`**：路径编码（`/` 不编码，空格→`%20`）。
- **`quote_plus()`**：查询参数值编码（空格→`+`，`/` 编码）。
- **`urlencode()`**：直接生成完整查询字符串（自动调用 `quote_plus`）。

根据场景选择合适的方法，确保 URL 正确、安全地传输！ 🚀

##### 4 解码(unquote/unquote_plus/parse_qs[l])

###### unquote

函数原型：

```python
def unquote(string: str | bytes, encoding: str = "utf-8", errors: str = "replace") -> str
```

- **功能**：将 URL 编码的字符串（`%xx` 形式）解码回原始字符串。

- **特点**：

  - **`%20` 解码为空格**（` 空格 `）。
  - **不处理 `+`**（`+` 不会被转换为空格）。
  - 适用于 **路径（Path）、Fragment（锚点）** 的解码。

- **示例：**

  ```python
  from urllib.parse import unquote
  
  encoded_str = "%E4%BD%A0%E5%A5%BD%20World%21"
  decoded_str = unquote(encoded_str)
  print(decoded_str)  # 输出: "你好 World!"
  ```

  

###### unquote_plus

函数原型：

```python
def unquote_plus(string: str, encoding: str = "utf-8", errors: str = "replace") -> str
```

- **功能**：解码 URL 编码的字符串，**额外将 `+` 转换为空格**。

- **特点**：

  - **`%20` 和 `+` 都会解码为空格**。
  - 适用于 **查询参数（Query String）** 的解码（因为查询参数中的空格通常编码为 `+`）。

- **示例：**

  ```python
  from urllib.parse import unquote_plus
  
  encoded_str = "q=python+%26+java&page=1"
  decoded_str = unquote_plus(encoded_str)
  print(decoded_str)  # 输出: "q=python & java&page=1"
  ```

  

###### parse_qs

函数原型：

```python
def parse_qs(qs, keep_blank_values=False, strict_parsing=False,
             encoding='utf-8', errors='replace', max_num_fields=None, separator='&')->dict
```

- **功能**：将 **查询字符串（`?key1=val1&key2=val2`）解码为字典**。

- **特点**：

  - 返回 `Dict[str, List[str]]`（值总是列表，支持多值参数）。
  - 自动调用 `unquote_plus()` 解码键和值（`+` → 空格，`%xx` → 字符）。

- **示例：**

  ```python
  from urllib.parse import parse_qs
  
  query_string = "q=python+%26+java&page=1&lang=en&lang=zh"
  result = parse_qs(query_string)
  print(result)
  ```

  输出：

  ```python
  {
      'q': ['python & java'],  # + 和 %26 被解码
      'page': ['1'],
      'lang': ['en', 'zh']    # 多值合并为列表
  }
  ```

  

###### parse_qsl

函数原型：

```python
def parse_qsl(qs, keep_blank_values=False, strict_parsing=False,
              encoding='utf-8', errors='replace', max_num_fields=None, separator='&')->list
```

- **功能**：将 **查询字符串解码为元组列表**，保留重复键。

- **特点**：

  - 返回 `List[Tuple[str, str]]`（适合需要保持顺序或处理重复键的场景）。
  - 同样自动调用 `unquote_plus()` 解码。

- **示例：**

  ```python
  from urllib.parse import parse_qsl
  
  query_string = "q=python+%26+java&page=1&lang=en&lang=zh"
  result = parse_qsl(query_string)
  print(result)
  ```

  输出：

  ```python
  [
      ('q', 'python & java'),  # + 和 %26 被解码
      ('page', '1'),
      ('lang', 'en'),
      ('lang', 'zh')          # 重复键保留
  ]
  ```

###### 对比总结

| 函数             | 输入       | 输出                     | 处理 `+`        | 适用场景                   |
| :--------------- | :--------- | :----------------------- | :-------------- | :------------------------- |
| `unquote()`      | 编码字符串 | 字符串                   | ❌               | 路径、Fragment             |
| `unquote_plus()` | 编码字符串 | 字符串                   | ✅（`+` → 空格） | 查询参数                   |
| `parse_qs()`     | 查询字符串 | 字典（值自动合并为列表） | ✅               | 解析多值参数（如表单数据） |
| `parse_qsl()`    | 查询字符串 | 元组列表（保留重复键）   | ✅               | 需要保持顺序或重复键       |

### 处理相对URL(urljoin)

`urljoin`函数用于将一个相对 URL 和一个基础 URL 合并成一个完整的 URL。

```python
import urllib.parse

base_url = 'https://www.example.com/path/to/'
relative_url = 'resource'
full_url = urllib.parse.urljoin(base_url, relative_url)
print(full_url)
```

代码中，`urljoin`函数将相对 URL`relative_url`合并到基础 URL`base_url`上，生成一个完整的 URL。

## urllib.robotparser

`urllib.robotparser`是 Python 标准库`urllib`中的一个子模块，主要用于解析网站的`robots.txt`文件。`robots.txt`是一种放置在网站根目录下的文本文件，网站管理员可以通过该文件来指定搜索引擎爬虫或其他网络机器人可以访问哪些页面，不可以访问哪些页面，以此来保护网站的隐私和控制爬虫的访问行为。

#### 1. 基本使用流程

- **创建`RobotFileParser`对象**：使用`urllib.robotparser.RobotFileParser()`创建一个解析器对象。
- **设置`robots.txt`文件的 URL**：调用`set_url()`方法设置要解析的`robots.txt`文件的 URL。
- **读取并解析`robots.txt`文件**：调用`read()`方法读取并解析`robots.txt`文件内容。
- **检查是否允许访问**：使用`can_fetch()`方法检查指定的爬虫（由用户代理字符串标识）是否被允许访问某个 URL。

#### 2. 示例代码

```python
import urllib.robotparser

# 创建RobotFileParser对象
rp = urllib.robotparser.RobotFileParser()

# 设置robots.txt文件的URL
rp.set_url('https://www.example.com/robots.txt')

# 读取并解析robots.txt文件
rp.read()

# 检查是否允许访问某个URL
user_agent = '*'  # 表示所有爬虫
url = 'https://www.example.com/some-page'
can_fetch = rp.can_fetch(user_agent, url)

if can_fetch:
    print(f"允许访问 {url}")
else:
    print(f"不允许访问 {url}")
```

#### 3. 代码解释

- **`set_url(url)`**：该方法用于指定要解析的`robots.txt`文件的 URL。在实际使用中，通常是网站的根目录下的`robots.txt`文件，例如`https://www.example.com/robots.txt`。
- **`read()`**：此方法会从指定的 URL 读取`robots.txt`文件的内容，并进行解析。解析后，`RobotFileParser`对象会将规则存储在内部，以便后续的检查。
- **`can_fetch(useragent, url)`**：该方法用于检查指定的用户代理（即爬虫的标识）是否被允许访问指定的 URL。`useragent`参数可以是具体的爬虫名称，如`Googlebot`，也可以使用`*`表示所有爬虫。如果允许访问，返回`True`；否则返回`False`。

#### 4. 注意事项

- **网络请求问题**：如果`robots.txt`文件无法访问（例如网络故障、文件不存在等），`read()`方法可能会抛出异常，需要进行适当的错误处理。
- **规则更新**：`robots.txt`文件的规则可能会随时更新，因此在爬虫运行过程中，可能需要定期重新读取和解析该文件。

通过使用`urllib.robotparser`，爬虫开发者可以确保自己的爬虫遵守网站的访问规则，避免因违反规则而被网站封禁。

## urllib.error

`urllib.error` 模块用于 **处理 HTTP 请求过程中可能发生的异常**。它提供了两种主要的异常类，帮助开发者更优雅地捕获和处理网络请求错误。

### **1. 核心异常类**

#### (1) URLError（基础异常）

- **触发条件**：
  - 网络问题（如 DNS 解析失败、连接超时、服务器无响应）。
  - 无效的 URL 格式。
- **属性**：
  - `reason`：返回错误原因（通常是一个字符串或子异常对象，如 `socket.error`）。

+ **示例**

```python
from urllib.request import urlopen
from urllib.error import URLError

try:
    response = urlopen("http://this-url-does-not-exist.com")
except URLError as e:
    print(f"请求失败，原因: {e.reason}")
    # 输出示例: "请求失败，原因: [Errno -2] Name or service not known"
```

#### (2) HTTPError（`URLError` 的子类）

- **触发条件**：
  - 服务器返回了 **HTTP 错误状态码**（如 404、500 等）。
- **属性**：
  - `code`：HTTP 状态码（如 404）。
  - `reason`：错误描述（如 "Not Found"）。
  - `headers`：服务器的响应头（可选）。

+ **示例**

```python
from urllib.request import urlopen
from urllib.error import HTTPError

try:
    response = urlopen("https://httpbin.org/status/404")
except HTTPError as e:
    print(f"服务器返回错误状态码: {e.code} {e.reason}")
    # 输出: "服务器返回错误状态码: 404 NOT FOUND"
```

### 2. 异常处理的最佳实践

#### (1) 优先捕获 `HTTPError`，再捕获 `URLError`

由于 `HTTPError` 是 `URLError` 的子类，顺序很重要：

```python
try:
    response = urlopen("https://example.com/invalid-page")
except HTTPError as e:
    print(f"HTTP 错误: {e.code} {e.reason}")
except URLError as e:
    print(f"URL 错误: {e.reason}")
else:
    print("请求成功！")
```

#### (2) 检查 `reason` 的具体类型

`URLError.reason` 可能是其他异常（如 `socket.timeout`）：

```python
try:
    response = urlopen("https://example.com", timeout=0.001)  # 极短超时
except URLError as e:
    if isinstance(e.reason, socket.timeout):
        print("请求超时！")
```

### 3. 常见错误场景

| 异常类型         | 典型原因               | 解决方案                  |
| :--------------- | :--------------------- | :------------------------ |
| `HTTPError 404`  | 页面不存在             | 检查 URL 或重试           |
| `HTTPError 500`  | 服务器内部错误         | 联系服务提供商或重试      |
| `URLError`       | 网络断开、DNS 解析失败 | 检查网络连接或 URL 格式   |
| `socket.timeout` | 请求超时               | 增加 `timeout` 参数或重试 |

## urllib.request

用于打开和读取 URL，提供了高级的接口来处理不同类型的请求，像 HTTP、FTP 等协议的请求。

### 发送简单的 GET 请求

使用 `urlopen` 函数可以直接发送 GET 请求并获取响应内容。

```python
import urllib.request

#(1)定义一个url 就是你要访问的地址
url = "https://www.baidu11.com"

#(2) 模拟浏览器向服务器发送请求
response = urllib.request.urlopen(url)

#(3) 获取响应中的页面源码
content = response.read().decode("utf8")

#(4) 打印数据
print(content)
```

在上述代码中，`urlopen` 函数打开指定的 URL 并返回一个响应对象，通过调用该对象的 `read` 方法读取响应内容，最后使用 `decode` 方法将字节数据解码为字符串。若请求过程中出现错误，会捕获 `urllib.error.URLError` 异常并输出错误信息。

### 发送带请求头的 GET 请求

有时候需要在请求中添加自定义的请求头，比如设置 `User-Agent` 来模拟不同的浏览器。

> UA介绍 ：User Agent中文名为用户代理 ，简称  UA，它是一个特殊字符串头 ，使得服务器能够识别客户使用的操作系统 及版本、CPU 类型、浏览器及版本。浏览器内核、浏览器渲染引擎、浏览器语言、浏览器插件等

```python
import urllib.request

url = 'https://www.example.com'
# 创建请求对象
req = urllib.request.Request(url)
# 添加请求头
req.add_header('User-Agent', 'Mozilla/5.0')
try:
    response = urllib.request.urlopen(req)
    html = response.read().decode('utf-8')
    print(html)
except urllib.error.URLError as e:
    print(f"请求出错: {e}")
```

此代码中，先创建了一个 `Request` 对象，然后使用 `add_header` 方法添加了一个 `User - Agent` 请求头，最后将该请求对象传递给 `urlopen` 函数发送请求。

也可以通过字典先把所有头准备好，然后一起添加：

```python
#(2) 添加请求头
headers = {
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36'
}
req = urllib.request.Request(url, headers=headers, method='GET')

#(2) 发送请求
response = urllib.request.urlopen(req)
```

## 爬虫小案例

### 百度搜索

```python
import urllib.parse
import urllib.request

url = 'http://www.baidu.com/s?wd=' + urllib.parse.quote('小刚')

headers={
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0'
}

req = urllib.request.Request(url, headers=headers)
#print(req.full_url)

resp =  urllib.request.urlopen(req)

content =  resp.read().decode('utf8')

with open('baidu.html','w',encoding='utf8') as file:
    file.write(content)
```

在这个示例中，首先定义了要提交的数据，使用 `urllib.parse.urlencode` 对数据进行编码，再将其转换为字节类型。接着创建一个 `Request` 对象，指定请求方法为 `POST`，并将编码后的数据作为请求体，最后发送请求并处理响应。

### 下载图片

把百度搜索首页的图片爬下来。

```python
url = 'https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png'

headers={
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0'
}

req = urllib.request.Request(url, headers=headers)

resp =  urllib.request.urlopen(req)

content =  resp.read()

with open('baidu.png','wb') as file:
    file.write(content)
```

### 下载视频

在好看视频随便下载一个视频。

```python
url = 'https://vdept3.bdstatic.com/mda-nkuhe4s3ja12t07i/360p/h264/1669724352552074273/mda-nkuhe4s3ja12t07i.mp4?v_from_s=hkapp-haokan-nanjing&auth_key=1746526848-0-0-c3d95151aaa5a772a603c500cedc1af7&bcevod_channel=searchbox_feed&pd=1&cr=0&cd=0&pt=3&logid=1248522976&vid=9245979460455935030&klogid=1248522976&abtest='

headers={
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0'
}

req = urllib.request.Request(url, headers=headers)

resp =  urllib.request.urlopen(req)

content =  resp.read()

with open('baidu.mp4','wb') as file:
    file.write(content)
```

### 百度翻译

#### 简单翻译

```python
url = 'https://fanyi.baidu.com/sug'

headers={
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0'
}

data={
    'kw':'你好'
}
#url编码并转成utf8的二进制
data = urllib.parse.urlencode(data).encode()

req = urllib.request.Request(url, headers=headers,method='POST')

resp =  urllib.request.urlopen(req,data=data)

content =  resp.read().decode('utf8')

print(content)
```

#### 译文读音

```python
text = input('input english>')

url = f'https://fanyi.baidu.com/gettts?lan=uk&text={urllib.parse.quote(text)}&spd=3'

headers={
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0'
}

req = urllib.request.Request(url,headers=headers,method='GET')

resp =  urllib.request.urlopen(req)

content =  resp.read()

with open('translate.mp3','wb') as file:
    file.write(content)

print('翻译发音下载完成~')
```

### 豆瓣电影

爬取豆瓣电影排行版前十页数据。

 ```python
 import urllib.parse
 import urllib.request
 
 def create_request(page : int):
     base_url = 'https://movie.douban.com/j/chart/top_list?type=5&interval_id=100%3A90&action=&'
 
     data ={
         'start':(page-1) * 20,
         'limit':20
     }
 
     headers ={
         'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0'
     }
 
     url = base_url + urllib.parse.urlencode(data)
     print(f"request url:{url}")
     return urllib.request.Request(url,headers=headers,method='GET')
 
 def download_conecnt(req):
     resp =  urllib.request.urlopen(req)
     content  = resp.read().decode('utf8')
     return content
 
 def save_content(page,content):
     with open(f'douban/douban_{page}.json','w',encoding='utf8') as fp:
         fp.write(content)
 
 if __name__ == '__main__':
     start_page = int(input('请输入起始页码:'))
     end_page = int(input('请输入结束页码:'))
     for i in range(start_page,end_page):
         req = create_request(i)
         content = download_conecnt(req)
         save_content(i,content)
 ```

## 12.cookie登录

 cookie的中文翻译是曲奇，小甜饼的意思。cookie其实就是一些数据信息，类型为“**小型文本文件**”，存储于电脑上的文本文件中。

### **Cookie有什么用？**

我们想象一个场景，当我们打开一个网站时，如果这个网站我们曾经登录过，那么当我们再次打开网站时，发现就不需要再次登录了，而是直接进入了首页。例如bilibili，csdn等网站。

​    这是怎么做到的呢？其实就是游览器保存了我们的cookie，里面记录了一些信息，当然，这些cookie是服务器创建后返回给游览器的。浏览器只进行了保存。

### **Cookie的表示** 

​    一般情况下，cookie是以键值对进行表示的(key-value)，例如name=jack，这个就表示cookie的名字是name，cookie携带的值是jack。

当需要抓取一些，登录之后才能访问的网站时，我们需要先登录，获取cookie，然后在爬取时携带cookie！然后就不需要输入账号和密码了！

### 使用案例

#### qq空间的爬取

```python
import urllib.parse
import urllib.request

url = 'https://user.qzone.qq.com/466449822/infocenter'

headers ={
      'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0',
      'Cookie':'466449822_todaycount=0; 466449822_totalcount=22163; pgv_pvid=6293739165; RK=GTtkJOP7UR; ptcz=73618d32010d1041e2c6e3a176d9234f77908b003bced7b77bf93c2c718e1d21; qq_domain_video_guid_verify=367e0ea2d02e65c7; _qimei_uuid42=19109000a2f1007c57e9bf69eabf2d052ddca4c373; _qimei_fingerprint=ef098312f649e9df39a208d598941fcf; _qimei_h38=2159fc4157e9bf69eabf2d0502000004519109; pac_uid=0_shc8c2mDS4P2d; suid=user_0_shc8c2mDS4P2d; _qimei_q32=807781332a66161d5576401251820e12; _qimei_q36=13a761515416031741cf9784300015419101; __Q_w_s__QZN_TodoMsgCnt=1; _clck=mfzhub|1|fvh|0; uin=o0466449822; skey=@uPra0xo9u; p_uin=o0466449822; pt4_token=VCaXIO*vHOynaNY7dlLgvKJ4gNqEdu8F88OwwLp0Im0_; p_skey=jW3uo4Sg3lRORB56zUNWsxW9Jj7eQJ89z2GgWIJlTmw_; Loading=Yes; qz_screen=1920x1080; pgv_info=ssid=s7403978208; QZ_FE_WEBP_SUPPORT=1; __Q_w_s_hat_seed=1; cpu_performance_v8=1; domain_id=5; domainid=5',
}

req =  urllib.request.Request(url,headers=headers,method='GET')

def download_conecnt(req):
    resp =  urllib.request.urlopen(req)
    content  = resp.read().decode('utf8')
    return content

def save_content(filename,content):
    with open(filename,'w',encoding='utf8') as fp:
        fp.write(content)

if __name__ == '__main__':
        content = download_conecnt(req)
        save_content('qzone.html',content)
```

## 13.Handler处理器

为什么要学习handler？

urllib.request.urlopen(url) 不能定制请求头

urllib.request.Request(url,headers,data) 可以定制请求头

Handler

定制更高级的请求头（随着业务逻辑的复杂 请求对象的定制已经满足不了我们的需求（动态cookie和代理 不能使用请求对象的定制）

```python
eg:
import urllib.request
url = 'http://www.baidu.com ' headers = {
'User ‐ Agent ': 'Mozilla / 5.0(Windows NT 10.0;Win64;x64) AppleWebKit / 537.36(KHTML, likeGecko) Chrome / 74.0.3729.169Safari / 537.36 '
}
request = urllib.request.Request(url=url,headers=headers) 
handler = urllib.request.HTTPHandler()
opener = urllib.request.build_opener(handler) 
response = opener.open(request)
print(response.read().decode('utf‐8 '))
```

## 14.代理服务器

### 1. 代理的常用功能?

1. 突破自身IP访问限制 ，访问国外站点。 

2. 访问一些单位或团体内部资源

>  扩展 ：某大学FTP(前提是该代理地址在该资源的允许访问范围之内)，使用教育网内地址段免费代理服务器 ，就可以用于对教育网开放的各类FTP下载上传 ，以及各类资料查询共享等服务。

3. 提高访问速度

>  扩展 ：通常代理服务器都设置一个较大的硬盘缓冲区 ，当有外界的信息通过时 ，同时也将其保存到缓冲 区中 ，当其他用户再访问相同的信息时 ， 则直接由缓冲区中取出信息 ，传给用户 ，以提高访问速度。

4. 隐藏真实IP

>  扩展 ：上网者也可以通过这种方法隐藏自己的IP，免受攻击。 

### 2. 代码配置代理

+ 创建Reuqest对象

+ 创建ProxyHandler对象

用handler对象创建opener对象 使用opener.open函数发送请求

 ```python
 import urllib.request
 
 url = 'https://ip.900cha.com/' 
 
 headers = {
     'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/136.0.0.0 Safari/537.36 Edg/136.0.0.0'
 }
 
 req = urllib.request.Request(url=url,headers=headers) 
 
 # 用户名密码认证(私密代理/独享代理)
 username = "csjtjrou"
 password = "efj5su30"
 proxies = {
     "https": "http://%(user)s:%(pwd)s@%(proxy)s/" % {"user": username, "pwd": password, "proxy": "113.250.49.145:16818"},
 }
 
 handler = urllib.request.ProxyHandler(proxies=proxies)
 
 opener = urllib.request.build_opener(handler) 
 
 response = opener.open(req)
 
 content = response.read().decode('utf-8')
 
 with open( 'daili.html ', 'w',encoding= 'utf-8')as fp: 
     fp.write(content)
 ```

### 3.代理网站

[永久免费公共代理池](https://proxy.scdn.io/?page=6&per_page=10)

[快代理 - 企业级HTTP代理IP云服务_专注IP代理11年](https://www.kuaidaili.com/?ref=d0zvi83mvmas)

