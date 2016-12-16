#include "stdafx.h"
#include "../HTTPURL/HttpUrl.h"
#include "../HTTPURL/UrlParsingError.h"

BOOST_AUTO_TEST_SUITE(HttpUrl)

	BOOST_AUTO_TEST_CASE(can_be_created_from_string_with_string_domain)
	{
		CHttpUrl url("https://localhost/index.html");
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
		BOOST_CHECK_EQUAL(url.GetDomain(), "localhost");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://localhost/index.html");
	}

	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_protocol)
	{
		try
		{
			CHttpUrl url("hsspt://local.host/index.html");
		}
		catch (CUrlParsingError & err)
		{
			BOOST_CHECK_EQUAL(err.what(), "Incorrect protocol");
		}
	}

	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_domain)
	{
		try
		{
			CHttpUrl url("https:///index.html");
		}
		catch (CUrlParsingError & err)
		{
			BOOST_CHECK_EQUAL(err.what(), "Incorrect domain");
		}
	}
	
	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_port)
	{
		try
		{
			CHttpUrl url("https://localhost:0/index.html");
		}
		catch (CUrlParsingError & err)
		{
			BOOST_CHECK_EQUAL(err.what(), "Incorrect port");
		}
		try
		{
			CHttpUrl url("https://localhost:port/index.html");
		}
		catch (CUrlParsingError & err)
		{
			BOOST_CHECK_EQUAL(err.what(), "Incorrect port");
		}
	}

	BOOST_AUTO_TEST_CASE(can_NOT_be_created_from_string_with_incorrect_document)
	{
		try
		{
			CHttpUrl url("https://localhost//");
		}
		catch (CUrlParsingError & err)
		{
			BOOST_CHECK_EQUAL(err.what(), "Incorrect document");
		}
	}

	BOOST_AUTO_TEST_CASE(can_be_created_from_string_with_standart_port)
	{
		CHttpUrl url("https://127.0.0.1/index.html");
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
		BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://127.0.0.1/index.html");
	}
	
	BOOST_AUTO_TEST_CASE(can_be_created_from_string_with_custom_port)
	{
		CHttpUrl url("https://127.0.0.1:344/index.html");
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
		BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
		BOOST_CHECK_EQUAL(url.GetPort(), 344);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://127.0.0.1:344/index.html");
	}

	BOOST_AUTO_TEST_CASE(can_be_create_with_user_data_with_standart_port)
	{
		CHttpUrl url("127.0.0.1", "index.html", HTTPS, 443);
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
		BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
		BOOST_CHECK_EQUAL(url.GetPort(), 443);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://127.0.0.1/index.html");
	}

	BOOST_AUTO_TEST_CASE(can_be_create_with_user_data_with_custom_port)
	{
		CHttpUrl url("127.0.0.1", "index.html", HTTPS, 7000);
		BOOST_CHECK_EQUAL(url.GetProtocol(), HTTPS);
		BOOST_CHECK_EQUAL(url.GetDocument(), "/index.html");
		BOOST_CHECK_EQUAL(url.GetDomain(), "127.0.0.1");
		BOOST_CHECK_EQUAL(url.GetPort(), 7000);
		BOOST_CHECK_EQUAL(url.GetURL(), "https://127.0.0.1:7000/index.html");
	}

BOOST_AUTO_TEST_SUITE_END()
