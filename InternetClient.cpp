#include "stdafx.h"
#include "InternetClient.h"

void InternetClient::InitCodesDescr()
{
	 m_CodesDescriptions[100] = L"Continue";
	 m_CodesDescriptions[101] = L"Switching Protocol";
	 m_CodesDescriptions[200] = L"OK";
	 m_CodesDescriptions[201] = L"Created";
	 m_CodesDescriptions[202] = L"Accepted";
	 m_CodesDescriptions[203] = L"Non-Authoritative Information";
	 m_CodesDescriptions[204] = L"No Content";
	 m_CodesDescriptions[205] = L"Reset Content";
	 m_CodesDescriptions[206] = L"Partial Content";
	 m_CodesDescriptions[300] = L"Multiple Choice";
	 m_CodesDescriptions[301] = L"Moved Permanently";
	 m_CodesDescriptions[302] = L"Found";
	 m_CodesDescriptions[303] = L"See Other";
	 m_CodesDescriptions[304] = L"Not Modified";
	 m_CodesDescriptions[305] = L"Use Proxy";
	 m_CodesDescriptions[306] = L"unused";
	 m_CodesDescriptions[307] = L"Temporary Redirect";
	 m_CodesDescriptions[308] = L"Permanent Redirect";
	 m_CodesDescriptions[400] = L"Bad Request";
	 m_CodesDescriptions[401] = L"Unauthorized";
	 m_CodesDescriptions[402] = L"Payment Required";
	 m_CodesDescriptions[403] = L"Forbidden";
	 m_CodesDescriptions[404] = L"Not Found";
	 m_CodesDescriptions[405] = L"Method Not Allowed";
	 m_CodesDescriptions[406] = L"Not Acceptable";
	 m_CodesDescriptions[407] = L"Proxy Authentication Required";
	 m_CodesDescriptions[408] = L"Request Timeout";
	 m_CodesDescriptions[409] = L"Conflict";
	 m_CodesDescriptions[410] = L"Gone";
	 m_CodesDescriptions[411] = L"Length Required";
	 m_CodesDescriptions[412] = L"Precondition Failed";
	 m_CodesDescriptions[413] = L"Request Entity Too Large";
	 m_CodesDescriptions[414] = L"Request-URI Too Long";
	 m_CodesDescriptions[415] = L"Unsupported Media Type";
	 m_CodesDescriptions[416] = L"Requested Range Not Satisfiable";
	 m_CodesDescriptions[417] = L"Expectation Failed";
	 m_CodesDescriptions[429] = L"Too Many Requests";
	 m_CodesDescriptions[451] = L"Unavailable For Legal Reasons";
	 m_CodesDescriptions[500] = L"Internal Server Error";
	 m_CodesDescriptions[501] = L"Not Implemented";
	 m_CodesDescriptions[502] = L"Bad Gateway";
	 m_CodesDescriptions[503] = L"Service Unavailable";
	 m_CodesDescriptions[504] = L"Gateway Timeout";
	 m_CodesDescriptions[505] = L"HTTP Version Not Supported";
	 m_CodesDescriptions[510] = L"Not Extended";
	 m_CodesDescriptions[511] = L"Network Authentication Required";
	 m_CodesDescriptions[599] = L"Network connect timeout error";

	 m_SynoCodesDescriptions[400] = L"File upload failed";
	 m_SynoCodesDescriptions[401] = L"Max number of tasks reached";
	 m_SynoCodesDescriptions[402] = L"Destination denied";
	 m_SynoCodesDescriptions[403] = L"Destination does not exist";
	 m_SynoCodesDescriptions[404] = L"Invalid task id";
	 m_SynoCodesDescriptions[405] = L"Invalid task action";
	 m_SynoCodesDescriptions[406] = L"No default destination";
	 m_SynoCodesDescriptions[407] = L"Set destination failed";
	 m_SynoCodesDescriptions[408] = L"File does not exist";

	 m_SynoCodesDescriptions[100] = L"Unknown error";
	 m_SynoCodesDescriptions[101] = L"Invalid parameter";
	 m_SynoCodesDescriptions[102] = L"The requested API does not exist";
	 m_SynoCodesDescriptions[103] = L"The requested method does not exist";
	 m_SynoCodesDescriptions[104] = L"The requested version does not support the functionality";
	 m_SynoCodesDescriptions[105] = L"The logged in session does not have permission";
	 m_SynoCodesDescriptions[106] = L"Session timeout";
	 m_SynoCodesDescriptions[107] = L"Session interrupted by duplicate login";

}

InternetClient::InternetClient()
{
	InitCodesDescr();
}

InternetClient::~InternetClient()
{
	m_session.Close();
}

CString InternetClient::GetCodeDescription(DWORD code)
{
	m_it = m_CodesDescriptions.find(code);
	if (m_it != m_CodesDescriptions.end())
		return m_it->second;
	else
		return L"Look at the description on the Internet";
}

CString InternetClient::GetSynoCodeDescription(DWORD code)
{
	m_it = m_SynoCodesDescriptions.find(code);
	if (m_it != m_SynoCodesDescriptions.end())
		return m_it->second;
	else
		return L"unknown";
}

HTTPResponse InternetClient::GetURL(CString* URL)
{
	HTTPResponse RetVal; //return RetVal;
	
	CHttpFile* pFile = (CHttpFile *)m_session.OpenURL(URL->GetString());

	DWORD dwStatus;
	
	m_Response = L"";

	pFile->QueryInfoStatusCode(dwStatus);
	if (dwStatus != 200)
	{
		m_Response.Format(L"The server has returned the code: %u (%s)", dwStatus, GetCodeDescription(dwStatus));
		RetVal.strResponse = m_Response;
		RetVal.code = dwStatus;
		return RetVal;
	}

	char *szBuff = new char[1024]; ZeroMemory(szBuff, 1);
	UINT nRead = pFile->Read(szBuff, 1024);
	while (nRead > 0)
	{
		m_Response = m_Response + CString(szBuff, nRead);
		nRead = pFile->Read(szBuff, 1024);
	}

	delete[] szBuff; szBuff = NULL;
	pFile->Close();
	delete pFile; pFile = NULL;
	
	RetVal.strResponse = m_Response;
	RetVal.code = dwStatus;

	return RetVal;
}

//HTTPResponse InternetClient::PostFile(CString BaseURL, CString URL, CString* Path, CString* Params)
//{
//	HINTERNET hInetSession;
//	CString strURL; CString strStop;
//	char cBuf[200001];
//	DWORD dwRead;
//	int dwReaded = 0;
//
//	HTTPResponse RetVal;
//
//	hInetSession = InternetOpen(L"DS Helper", INTERNET_OPEN_TYPE_PRECONFIG, NULL, 0, 0);
//	if (!hInetSession)
//		return RetVal;
//
//	HINTERNET hConnect = InternetConnect(hInetSession, L"192.168.1.10", 5000, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1u);
//	if (!hConnect) { InternetCloseHandle(hInetSession); return RetVal; }
//
//	strURL = "/webapi/DownloadStation/task.cgi";
//
//	HINTERNET hRequest = HttpOpenRequest(hConnect, L"POST", strURL, NULL, NULL, 0, INTERNET_FLAG_KEEP_CONNECTION, 1); // Пост запрос
//	if (!hRequest) { InternetCloseHandle(hConnect); InternetCloseHandle(hInetSession); return RetVal; }
//
//	BOOL bSend; CString strAdd;
//	strAdd = "Content-Type: multipart/form-data; boundary=---------------------------212812725711114"; // Тип контента
//	bSend = ::HttpAddRequestHeaders(hRequest, strAdd, strAdd.GetLength(), HTTP_ADDREQ_FLAG_ADD); // Добавляем необходимые параметры запроса
//	/*strAdd = "Accept-Encoding: compress, gzip";
//	bSend = ::HttpAddRequestHeaders(hRequest, strAdd.c_str(), strAdd.length(), HTTP_ADDREQ_FLAG_ADD);
//	strAdd = "Accept: text/html, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap";
//	bSend = ::HttpAddRequestHeaders(hRequest, strAdd.c_str(), strAdd.length(), HTTP_ADDREQ_FLAG_ADD);*/
//
//	//strAdd = "text=Transformers&movie=1"; // Здесь передаются необходимые переменные
//	//// По аналогии: "pass=123&username=user&flag=1"
//
//	//bSend = ::HttpSendRequest(hRequest, NULL, 0, (void*)strAdd.GetString(), strAdd.GetLength());
//	::HttpSendRequest(
//	::HttpSendRequestEx(hRequest,)
//
//	if (!bSend)
//	{
//		InternetCloseHandle(hRequest);
//		InternetCloseHandle(hConnect);
//		InternetCloseHandle(hInetSession);
//		return RetVal;
//	}
//
//	unsigned long ulSource = 0;
//
//	InternetSetFilePointer(hRequest, 0, NULL, FILE_BEGIN, NULL);
//	InternetReadFile(hRequest, (LPVOID)&cBuf, 200000, &dwRead);
//	InternetCloseHandle(hRequest);
//}

HTTPResponse InternetClient::PostFile(CString BaseURL, CString URL, CString* Path, CStringA* Params)//stackoverflow.com/questions/158908/mfc-file-upload
{
	//forum.synology.com/enu/viewtopic.php?t=105325
	//forum.synology.com/enu/viewtopic.php?t=60788
	//forum.synology.com/enu/viewtopic.php?t=68339

	//CInternetSession ises = NULL;
	//CHttpFile* httpf = NULL;
	//CHttpConnection *connection = NULL;
	HTTPResponse RetVal;
	DWORD dwStatus(0);
	
	m_Response = L"";

	CFile* file = new CFile(Path->GetString(), CFile::modeRead | CFile::typeBinary);

	int Replaced = BaseURL.Replace(L"http://", L"");
	Replaced = BaseURL.Replace(L"https://", L"");

	DWORD flags(0);

	if (Replaced > 0)
		flags = INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE;//https 
	else
		flags = INTERNET_FLAG_KEEP_CONNECTION;
		//flags = INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_RAW_DATA | INTERNET_FLAG_EXISTING_CONNECT | INTERNET_FLAG_TRANSFER_BINARY;

	CHttpConnection* connection = m_session.GetHttpConnection(L"192.168.1.10", (INTERNET_PORT)5000);

	//CHttpFile* pFile = connection->OpenRequest(CHttpConnection::HTTP_VERB_POST, L"/webapi/DownloadStation/task.cgi", NULL, 1, NULL, NULL, flags);
	//CHttpFile* pFile = connection->OpenRequest(CHttpConnection::HTTP_VERB_POST, L"/webapi/DownloadStation/task.cgi");///webapi/entry.cgi/SYNO.DownloadStation2.Task
	CHttpFile* pFile = connection->OpenRequest(CHttpConnection::HTTP_VERB_POST, L"/webapi/DownloadStation/task.cgi");

	///*defines the connection timeout in ms*/
	//DWORD dwTimeout = 1200000;
	//InternetSetOption(*pFile, INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, &dwTimeout, sizeof(DWORD));
	//InternetSetOption(*pFile, INTERNET_OPTION_CONTROL_SEND_TIMEOUT, &dwTimeout, sizeof(DWORD));

	//CString hdrs = L"Content-Type: application/x/www-form-urlencoded";
	//pFile->AddRequestHeaders(hdrs, HTTP_ADDREQ_FLAG_ADD);
	//

	//CString hdrs = _T("Content-Type: multipart/form-data");//application/octet-stream
	//CString hdrs = _T("Content-Type: application/octet-stream");
	
	//CString hdrs = L"Accept: application/json, text/plain, */*\r\nContent-Type: multipart/form-data; boundary=dshelperpostrequestboundary";
	//CString hdrs = L"Content-Type: multipart/form-data; charset=utf-8; boundary=dshelperpostrequestboundary\r\nHost: 192.168.1.10";

	//CT2CA pszConvertedAnsiString(hdrs);
	
	//pFile->AddRequestHeaders(L"Accept: application/json, text/plain, */*\r\n", HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);
	pFile->AddRequestHeaders(L"Content-Type: multipart/form-data; boundary=---------------------------6876121865\r\n", HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);
	//pFile->AddRequestHeaders(L"Host: 192.168.1.10\r\n", HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);
	//pFile->AddRequestHeaders(L"Connection: keep-alive\r\n", HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);
	//pFile->AddRequestHeaders(L"Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3\r\n", HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);
	//pFile->AddRequestHeaders(L"User-Agent: DS Helper\r\n", HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);
	

	//pFile->AddRequestHeaders(hdrs, HTTP_ADDREQ_FLAG_ADD);
	//pFile->AddRequestHeaders(hdrs, HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);
	//
	//

	CStringA b("-----------------------------6876121865\r\n");

	CStringA POST = b;
	//CStringA POST = "";
	POST = POST + "Content-Disposition: form-data; name=\"api\"\r\n\r\n";
	POST = POST + "SYNO.DownloadStation.Task\r\n";
	POST = POST + b;
	POST = POST + "Content-Disposition: form-data; name=\"version\"\r\n\r\n";
	POST = POST + "1\r\n"; 
	POST = POST + b;
	POST = POST + "Content-Disposition: form-data; name=\"method\"\r\n\r\n";
	POST = POST + "create\r\n";
	//POST = POST + b;
	//POST = POST + "Content-Disposition: form-data; name=\"type\"\r\n\r\n";
	//POST = POST + "\"file\"\r\n";
	//POST = POST + b;
	//POST = POST + "Content-Disposition: form-data; name=\"file\"\r\n\r\n";
	//POST = POST + "[\"torrent\"]\r\n";
	POST = POST + b;
	POST = POST + "Content-Disposition: form-data; name=\"destination\"\r\n\r\n";
	POST = POST + "video/movie\r\n";
	//POST = POST + b;
	//POST = POST + "Content-Disposition: form-data; name=\"create_list\"\r\n\r\n";
	//POST = POST + "false\r\n";
	//POST = POST + b;
	//POST = POST + "Content-Disposition: form-data; name=\"mtime\"\r\n\r\n";
	//POST = POST + "1496756530471\r\n";
	//POST = POST + b;
	//POST = POST + "Content-Disposition: form-data; name=\"size\"\r\n\r\n";
	//POST = POST + "14860\r\n";
	//POST = POST + b;
	//POST = POST + "Content-Disposition: form-data; name=\"sid\"\r\n\r\n";
	//POST = POST + Params->GetString() + "\r\n";
	//POST = POST + b;
	//POST = POST + "Content-Disposition: form-data; name=\"_sid\"\r\n\r\n";
	//POST = POST + Params->GetString() + "\r\n";
	POST = POST + b;
	POST = POST + "Content-Disposition: form-data; name=\"file\"; filename=\"test.torrent\"\r\n";
	//POST = POST + "Content-Type: application/octet-stream\r\nContent-Transfer-Encoding: binary\r\n\r\n";
	POST = POST + "Content-Type: application/octet-stream\r\n\r\n";
	//POST = POST + "Content-Type: application/x-bittorrent\r\n\r\n";
	
	CStringA POSTp = "\r\n\r\n---------------------------6876121865--\r\n";
	//DWORD length = file->GetLength(); length = 0;
	pFile->SendRequestEx(DWORD(POST.GetLength() + file->GetLength() + POSTp.GetLength()), HSR_SYNC | HSR_INITIATE);

	pFile->Write(POST, POST.GetLength());
	
	
	char szBuff[1024];
	 DWORD nRead = file->Read(&szBuff, 1024);
	while (nRead > 0)
	{
		//length = length + nRead;
		pFile->Write(&szBuff, nRead);
		//POST = POST + CStringA(szBuff, nRead);
		nRead = file->Read(&szBuff, 1024);
	}
	file->Close(); delete file;

	//POST = POST + POSTp;

	//DWORD length = POST.GetLength();

	
	pFile->Write(POSTp, POSTp.GetLength());


	//pFile->SendRequest(hdrs, (LPVOID)POST.GetString(), length);

	/*char szBuff[1024];
	UINT nRead = file->Read(&szBuff, 1024);
	while (nRead > 0)
	{
		pFile->Write(&szBuff, nRead);
		nRead = file->Read(&szBuff, 1024);
	}
	file->Close(); delete file;*/

	//pFile->Write(POSTp, POSTp.GetLength());

	pFile->EndRequest(HSR_SYNC);
	//pFile->EndRequest();
	
	//CString t;

	//char szBuff[1024];
	//UINT nRead = file->Read(&szBuff, 1024);
	//while (nRead > 0)
	//{
	//	t = t + CString(szBuff, nRead);
	//	nRead = file->Read(&szBuff, 1024);
	//}
	//t = Params->GetString() + t;
	//pFile->SendRequest(hdrs, (LPVOID)(LPCTSTR)t, t.GetLength());
	
	pFile->QueryInfoStatusCode(dwStatus);
	if (dwStatus != 200)
	{
		m_Response.Format(L"The server has returned the code: %u (%s)", dwStatus, GetCodeDescription(dwStatus));
		RetVal.strResponse = m_Response;
		RetVal.code = dwStatus;
		return RetVal;
	}

	ZeroMemory(szBuff, 1);
	nRead = pFile->Read(szBuff, 1024);
	while (nRead > 0)
	{
		m_Response = m_Response + CString(szBuff, nRead);
		nRead = pFile->Read(szBuff, 1024);
	}

	AfxMessageBox(m_Response);

	//CFile* file_ = new CFile;
	//file_->Open(_T("D:\\HomeDirs\\Evgeny\\work\\c++\\DS Helper\\_1.txt"), CFile::modeCreate | CFile::modeReadWrite);

	//file_->Write(POST, POST.GetLength());
	//file_->Flush();
	//file_->Close();
	//delete file_;

	pFile->Close();
	connection->Close();


	RetVal.strResponse = m_Response;
	RetVal.code = dwStatus;

	return RetVal;
}