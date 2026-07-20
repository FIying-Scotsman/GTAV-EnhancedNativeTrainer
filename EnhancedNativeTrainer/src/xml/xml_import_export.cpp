/*
Part of the Enhanced Native Trainer project.
https://github.com/gtav-ent/GTAV-EnhancedNativeTrainer
(C) Rob Pridham and fellow contributors 2015
*/

// exclude(): ISequentialStream/_FILETIME are already declared via other Windows headers pulled in
// elsewhere in this translation unit - the importer silently skips redeclaring them regardless,
// this just makes that explicit instead of emitting a C4192 warning about it.
#import <msxml6.dll> exclude("ISequentialStream", "_FILETIME") //read the GitHub project readme regarding what you need to make this work

#include "xml_import_export.h"
#include "..\version.h"
#include "..\features\script.h"

#include "..\debug\debuglog.h"

// A global Windows "basic string". Actual memory is allocated by the
// COM methods used by MSXML which take &keyconf_bstr. We must use SysFreeString()
// to free this memory before subsequent uses, to prevent a leak.
BSTR xmlParser_bstr;

// Internal helpers - not used outside this file, so the COM types they take
// don't need to leak into xml_import_export.h (and its #import with them).
static void handle_error(IXMLDOMDocumentPtr doc);
static bool format_dom_document(IXMLDOMDocument *pDoc, IStream *pStream);

bool generate_xml_for_propset(SavedPropSet* props, std::string outputFile)
{
	//Create the XML
	IXMLDOMDocumentPtr pXMLDoc;
	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if (FAILED(hr))
	{
		write_text_to_log_file("Failed to create the XML class instance");
		return false;
	}

	VARIANT_BOOL bIsSuccessful;
	if (FAILED(pXMLDoc->loadXML(L"<object-set></object-set>", &bIsSuccessful)))
	{
		write_text_to_log_file("Root creation failed");
		handle_error(pXMLDoc);
		return false;
	}

	IXMLDOMProcessingInstructionPtr pXMLProcessingNode;
	pXMLDoc->createProcessingInstruction(L"xml", L" version=\"1.0\" encoding=\"UTF-8\"", &pXMLProcessingNode);

	//Get the root element just created    
	IXMLDOMElementPtr pXMLRootElem;
	pXMLDoc->get_documentElement(&pXMLRootElem);

	_variant_t vtObject;
	vtObject.vt = VT_DISPATCH;
	vtObject.pdispVal = pXMLRootElem;
	vtObject.pdispVal->AddRef();
	pXMLDoc->insertBefore(pXMLProcessingNode, vtObject, 0);

	//Add an attribute
	pXMLRootElem->setAttribute(L"set-name", _variant_t(props->saveName.c_str()));
	pXMLRootElem->setAttribute(L"ent-version", _variant_t(VERSION_STRING.c_str()));

	for each (SavedPropDBRow* row in props->items)
	{
		//Create child element
		IXMLDOMElementPtr objectNode;
		pXMLDoc->createElement(L"object", &objectNode);

		objectNode->setAttribute(L"title", _variant_t(row->title.c_str()));
		objectNode->setAttribute(L"model", _variant_t((long)(row->model)));

		objectNode->setAttribute(L"posX", _variant_t(row->posX));
		objectNode->setAttribute(L"posY", _variant_t(row->posY));
		objectNode->setAttribute(L"posZ", _variant_t(row->posZ));

		objectNode->setAttribute(L"roll", _variant_t(row->roll));
		objectNode->setAttribute(L"pitch", _variant_t(row->pitch));
		objectNode->setAttribute(L"yaw", _variant_t(row->yaw));

		objectNode->setAttribute(L"isImmovable", _variant_t(row->isImmovable));
		objectNode->setAttribute(L"isInvincible", _variant_t(row->isInvincible));
		objectNode->setAttribute(L"hasGravity", _variant_t(row->hasGravity));

		objectNode->setAttribute(L"alpha", _variant_t(row->alpha));
		objectNode->setAttribute(L"counter", _variant_t(row->counter));

		pXMLRootElem->appendChild(objectNode, 0);
	}

	FileStream* output;
	std::wstring ws;
	ws.assign(outputFile.begin(), outputFile.end());
	BSTR bs = SysAllocStringLen(ws.data(), ws.size());

	bool result = true;
	if (FAILED(FileStream::OpenFile(bs, &output, true)))
	{
		write_text_to_log_file("Opening output failed");
		result = false;
	}
	else
	{
		if (!format_dom_document(pXMLDoc, output))
		{
			write_text_to_log_file("Save failed");
			write_text_to_log_file(outputFile);
			handle_error(pXMLDoc);
			result = false;
		}
		else
		{
			write_text_to_log_file("Save complete");
			write_text_to_log_file(outputFile);
			result = true;
		}

		int count = 0;
		do
		{
			count = output->Release();
		} while (count > 0);

		if (count == 0)
		{
			write_text_to_log_file("File closed, zero count");
		}
		else
		{
			write_text_to_log_file("File closed, non-zero count");
		}
	}
	return result;
}

bool parse_xml_for_propset(std::string inputFile, SavedPropSet* set)
{
	CoInitialize(NULL);

	//read XML
	MSXML2::IXMLDOMDocumentPtr spXMLDoc;
	spXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if (!spXMLDoc->load(inputFile.c_str()))
	{
		write_text_to_log_file("No XML file found");
		return false;
	}

	IXMLDOMNodeListPtr topNodes = spXMLDoc->selectNodes(L"//object-set");
	{
		IXMLDOMNode *node;
		topNodes->get_item(0, &node);

		IXMLDOMNamedNodeMap *attribs;
		node->get_attributes(&attribs);
		long length_attribs;
		attribs->get_length(&length_attribs);

		for (long j = 0; j < length_attribs; j++)
		{
			IXMLDOMNode *attribNode;
			attribs->get_item(j, &attribNode);
			attribNode->get_nodeName(&xmlParser_bstr);
			if (wcscmp(xmlParser_bstr, L"set-name") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				set->saveName = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}

			SysFreeString(xmlParser_bstr);
			attribNode->Release();
		}

		attribs->Release();
		node->Release();
	}

	IXMLDOMNodeListPtr nodes = spXMLDoc->selectNodes(L"//object-set/object");
	long length;
	nodes->get_length(&length);
	for (int i = 0; i < length; i++)
	{
		WAIT(0);
		make_periodic_feature_call();

		IXMLDOMNode *node;
		nodes->get_item(i, &node);
		IXMLDOMNamedNodeMap *attribs;
		node->get_attributes(&attribs);

		SavedPropDBRow* row = new SavedPropDBRow();

		long length_attribs;
		attribs->get_length(&length_attribs);

		for (long j = 0; j < length_attribs; j++)
		{
			IXMLDOMNode *attribNode;
			attribs->get_item(j, &attribNode);
			attribNode->get_nodeName(&xmlParser_bstr);
			if (wcscmp(xmlParser_bstr, L"title") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				row->title = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}
			else if (wcscmp(xmlParser_bstr, L"model") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_I8);
				row->model = var.intVal;
			}
			else if (wcscmp(xmlParser_bstr, L"posX") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_R4);
				row->posX = var.fltVal;
			}
			else if (wcscmp(xmlParser_bstr, L"posY") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_R4);
				row->posY = var.fltVal;
			}
			else if (wcscmp(xmlParser_bstr, L"posZ") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_R4);
				row->posZ = var.fltVal;
			}
			else if (wcscmp(xmlParser_bstr, L"roll") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_R4);
				row->roll = var.fltVal;
			}
			else if (wcscmp(xmlParser_bstr, L"pitch") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_R4);
				row->pitch = var.fltVal;
			}
			else if (wcscmp(xmlParser_bstr, L"yaw") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_R4);
				row->yaw = var.fltVal;
			}
			else if (wcscmp(xmlParser_bstr, L"isImmovable") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_INT);
				row->isImmovable = var.intVal;
			}
			else if (wcscmp(xmlParser_bstr, L"isInvincible") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_INT);
				row->isInvincible = var.intVal;
			}
			else if (wcscmp(xmlParser_bstr, L"hasGravity") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_INT);
				row->hasGravity = var.intVal;
			}
			else if (wcscmp(xmlParser_bstr, L"alpha") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_INT);
				row->alpha = var.intVal;
			}

			SysFreeString(xmlParser_bstr);
			attribNode->Release();
		}

		row->counter = 0;
		set->items.push_back(row);

		attribs->Release();
		node->Release();
	}

	set->dbSize = set->items.size();

	//nodes->Release(); //don't do this, it crashes on exit
	spXMLDoc.Release();
	CoUninitialize();

	return true;
}

bool generate_xml_for_interior_customization(SavedInteriorCustomization* data, std::string outputFile)
{
	IXMLDOMDocumentPtr pXMLDoc;
	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if (FAILED(hr))
	{
		write_text_to_log_file("Failed to create the XML class instance");
		return false;
	}

	VARIANT_BOOL bIsSuccessful;
	if (FAILED(pXMLDoc->loadXML(L"<interior-customization></interior-customization>", &bIsSuccessful)))
	{
		write_text_to_log_file("Root creation failed");
		handle_error(pXMLDoc);
		return false;
	}

	IXMLDOMProcessingInstructionPtr pXMLProcessingNode;
	pXMLDoc->createProcessingInstruction(L"xml", L" version=\"1.0\" encoding=\"UTF-8\"", &pXMLProcessingNode);

	IXMLDOMElementPtr pXMLRootElem;
	pXMLDoc->get_documentElement(&pXMLRootElem);

	_variant_t vtObject;
	vtObject.vt = VT_DISPATCH;
	vtObject.pdispVal = pXMLRootElem;
	vtObject.pdispVal->AddRef();
	pXMLDoc->insertBefore(pXMLProcessingNode, vtObject, 0);

	pXMLRootElem->setAttribute(L"interior-name", _variant_t(data->interiorName.c_str()));
	pXMLRootElem->setAttribute(L"ent-version", _variant_t(VERSION_STRING.c_str()));

	for (const SavedInteriorCategorySelection& category : data->categories)
	{
		IXMLDOMElementPtr categoryNode;
		pXMLDoc->createElement(L"category", &categoryNode);

		categoryNode->setAttribute(L"name", _variant_t(category.categoryName.c_str()));
		categoryNode->setAttribute(L"option", _variant_t(category.selectedOptionName.c_str()));
		categoryNode->setAttribute(L"tint", _variant_t(category.tint));

		pXMLRootElem->appendChild(categoryNode, 0);
	}

	for (const SavedInteriorPropSelection& prop : data->props)
	{
		IXMLDOMElementPtr propNode;
		pXMLDoc->createElement(L"prop", &propNode);

		propNode->setAttribute(L"name", _variant_t(prop.propName.c_str()));
		propNode->setAttribute(L"active", _variant_t(prop.active));

		pXMLRootElem->appendChild(propNode, 0);
	}

	FileStream* output;
	std::wstring ws;
	ws.assign(outputFile.begin(), outputFile.end());
	BSTR bs = SysAllocStringLen(ws.data(), ws.size());

	bool result = true;
	if (FAILED(FileStream::OpenFile(bs, &output, true)))
	{
		write_text_to_log_file("Opening output failed");
		result = false;
	}
	else
	{
		if (!format_dom_document(pXMLDoc, output))
		{
			write_text_to_log_file("Save failed");
			write_text_to_log_file(outputFile);
			handle_error(pXMLDoc);
			result = false;
		}
		else
		{
			write_text_to_log_file("Save complete");
			write_text_to_log_file(outputFile);
			result = true;
		}

		int count = 0;
		do
		{
			count = output->Release();
		} while (count > 0);
	}
	return result;
}

bool parse_xml_for_interior_customization(std::string inputFile, SavedInteriorCustomization* data)
{
	CoInitialize(NULL);

	MSXML2::IXMLDOMDocumentPtr spXMLDoc;
	spXMLDoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
	if (!spXMLDoc->load(inputFile.c_str()))
	{
		write_text_to_log_file("No XML file found");
		return false;
	}

	IXMLDOMNodeListPtr topNodes = spXMLDoc->selectNodes(L"//interior-customization");
	{
		IXMLDOMNode *node;
		topNodes->get_item(0, &node);

		IXMLDOMNamedNodeMap *attribs;
		node->get_attributes(&attribs);
		long length_attribs;
		attribs->get_length(&length_attribs);

		for (long j = 0; j < length_attribs; j++)
		{
			IXMLDOMNode *attribNode;
			attribs->get_item(j, &attribNode);
			attribNode->get_nodeName(&xmlParser_bstr);
			if (wcscmp(xmlParser_bstr, L"interior-name") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				data->interiorName = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}

			SysFreeString(xmlParser_bstr);
			attribNode->Release();
		}

		attribs->Release();
		node->Release();
	}

	IXMLDOMNodeListPtr categoryNodes = spXMLDoc->selectNodes(L"//interior-customization/category");
	long categoryCount;
	categoryNodes->get_length(&categoryCount);
	for (int i = 0; i < categoryCount; i++)
	{
		WAIT(0);
		make_periodic_feature_call();

		IXMLDOMNode *node;
		categoryNodes->get_item(i, &node);
		IXMLDOMNamedNodeMap *attribs;
		node->get_attributes(&attribs);

		SavedInteriorCategorySelection category;

		long length_attribs;
		attribs->get_length(&length_attribs);

		for (long j = 0; j < length_attribs; j++)
		{
			IXMLDOMNode *attribNode;
			attribs->get_item(j, &attribNode);
			attribNode->get_nodeName(&xmlParser_bstr);
			if (wcscmp(xmlParser_bstr, L"name") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				category.categoryName = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}
			else if (wcscmp(xmlParser_bstr, L"option") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				category.selectedOptionName = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}
			else if (wcscmp(xmlParser_bstr, L"tint") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_INT);
				category.tint = var.intVal;
			}

			SysFreeString(xmlParser_bstr);
			attribNode->Release();
		}

		data->categories.push_back(category);

		attribs->Release();
		node->Release();
	}

	IXMLDOMNodeListPtr propNodes = spXMLDoc->selectNodes(L"//interior-customization/prop");
	long propCount;
	propNodes->get_length(&propCount);
	for (int i = 0; i < propCount; i++)
	{
		WAIT(0);
		make_periodic_feature_call();

		IXMLDOMNode *node;
		propNodes->get_item(i, &node);
		IXMLDOMNamedNodeMap *attribs;
		node->get_attributes(&attribs);

		SavedInteriorPropSelection prop;

		long length_attribs;
		attribs->get_length(&length_attribs);

		for (long j = 0; j < length_attribs; j++)
		{
			IXMLDOMNode *attribNode;
			attribs->get_item(j, &attribNode);
			attribNode->get_nodeName(&xmlParser_bstr);
			if (wcscmp(xmlParser_bstr, L"name") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				prop.propName = _com_util::ConvertBSTRToString(V_BSTR(&var));
			}
			else if (wcscmp(xmlParser_bstr, L"active") == 0)
			{
				VARIANT var;
				VariantInit(&var);
				attribNode->get_nodeValue(&var);
				VariantChangeType(&var, &var, 0, VT_INT);
				prop.active = var.intVal != 0;
			}

			SysFreeString(xmlParser_bstr);
			attribNode->Release();
		}

		data->props.push_back(prop);

		attribs->Release();
		node->Release();
	}

	spXMLDoc.Release();
	CoUninitialize();

	return true;
}

static void handle_error(IXMLDOMDocumentPtr doc)
{
	std::ostringstream ss;
	IXMLDOMParseError* pError;
	ss << "XML error: ";
	doc->get_parseError(&pError);
	if (pError)
	{
		BSTR reasonStr;
		pError->get_reason(&reasonStr);
		ss << reasonStr;
	}
	else
	{
		ss << "Unknown";
	}
	write_text_to_log_file(ss.str());
}

static bool format_dom_document(IXMLDOMDocument *pDoc, IStream *pStream)
{
	// Create the writer
	MSXML2::IMXWriterPtr pMXWriter;
	
	if (FAILED(pMXWriter.CreateInstance(__uuidof(MSXML2::MXXMLWriter60))))
	{
		return false;
	}
	MSXML2::ISAXContentHandler* pISAXContentHandler;
	if (FAILED(pMXWriter->QueryInterface(&pISAXContentHandler)))
	{
		return false;
	}
	MSXML2::ISAXErrorHandler* pISAXErrorHandler;
	if (FAILED(pMXWriter->QueryInterface(&pISAXErrorHandler)))
	{
		return false;
	}
	MSXML2::ISAXDTDHandler* pISAXDTDHandler;
	if (FAILED(pMXWriter->QueryInterface(&pISAXDTDHandler)))
	{
		return false;
	}

	if (FAILED(pMXWriter->put_omitXMLDeclaration(VARIANT_FALSE)) ||
		FAILED(pMXWriter->put_standalone(VARIANT_TRUE)) ||
		FAILED(pMXWriter->put_indent(VARIANT_TRUE)) ||
		FAILED(pMXWriter->put_encoding(L"UTF-8")))
	{
		return false;
	}

	// Create the SAX reader
	MSXML2::ISAXXMLReaderPtr pSAXReader;
	if (FAILED(pSAXReader.CreateInstance(__uuidof (MSXML2::SAXXMLReader60))))
	{
		return false;
	}

	wchar_t lexical_handler[] = L"http://xml.org/sax/properties/lexical-handler";
	wchar_t declaration_handler[] = L"http://xml.org/sax/properties/declaration-handler";

	if (FAILED(pSAXReader->putContentHandler(pISAXContentHandler)) ||
		FAILED(pSAXReader->putDTDHandler(pISAXDTDHandler)) ||
		FAILED(pSAXReader->putErrorHandler(pISAXErrorHandler)) ||
		FAILED(pSAXReader->putProperty(reinterpret_cast<unsigned short*>(lexical_handler), _variant_t(pMXWriter.GetInterfacePtr()))) ||
		FAILED(pSAXReader->putProperty(reinterpret_cast<unsigned short*>(declaration_handler), _variant_t(pMXWriter.GetInterfacePtr()))))
	{
		return false;
	}

	// Perform the write
	bool success1 = SUCCEEDED(pMXWriter->put_output(_variant_t(pStream)));
	bool success2 = SUCCEEDED(pSAXReader->parse(pDoc));

	return success1 && success2;
}