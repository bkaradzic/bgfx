
namespace("Convert");


//
// Convert between utf8 and b64 without raising character out of range exceptions with unicode strings
// Technique described here: http://monsur.hossa.in/2012/07/20/utf-8-in-javascript.html
//
Convert.utf8string_to_b64string = function(str)
{
	return btoa(unescape(encodeURIComponent(str)));
}
Convert.b64string_to_utf8string = function(str)
{
	return decodeURIComponent(escape(atob(str)));
}


//
// More general approach, converting between byte arrays and b64
// Info here: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Base64_encoding_and_decoding
//
Convert.b64string_to_Uint8Array = function(sBase64, nBlocksSize)
{
	function b64ToUint6 (nChr)
	{
		return nChr > 64 && nChr < 91 ?
			nChr - 65
		: nChr > 96 && nChr < 123 ?
		nChr - 71
		: nChr > 47 && nChr < 58 ?
		nChr + 4
		: nChr === 43 ?
		62
		: nChr === 47 ?
		63
		:
		0;
	}

	var
		sB64Enc = sBase64.replace(/[^A-Za-z0-9\+\/]/g, ""),
		nInLen = sB64Enc.length,
		nOutLen = nBlocksSize ? Math.ceil((nInLen * 3 + 1 >> 2) / nBlocksSize) * nBlocksSize : nInLen * 3 + 1 >> 2,
		taBytes = new Uint8Array(nOutLen);

	for (var nMod3, nMod4, nUint24 = 0, nOutIdx = 0, nInIdx = 0; nInIdx < nInLen; nInIdx++)
	{
		nMod4 = nInIdx & 3;
		nUint24 |= b64ToUint6(sB64Enc.charCodeAt(nInIdx)) << 18 - 6 * nMod4;
		if (nMod4 === 3 || nInLen - nInIdx === 1)
		{
			for (nMod3 = 0; nMod3 < 3 && nOutIdx < nOutLen; nMod3++, nOutIdx++)
				taBytes[nOutIdx] = nUint24 >>> (16 >>> nMod3 & 24) & 255;
			nUint24 = 0;
		}
	}

	return taBytes;
}
Convert.Uint8Array_to_b64string = function(aBytes)
{
	function uint6ToB64 (nUint6)
	{
		return nUint6 < 26 ?
			nUint6 + 65
			: nUint6 < 52 ?
			nUint6 + 71
			: nUint6 < 62 ?
			nUint6 - 4
			: nUint6 === 62 ?
			43
			: nUint6 === 63 ?
			47
			:
			65;
	}

	var nMod3, sB64Enc = "";

	for (var nLen = aBytes.length, nUint24 = 0, nIdx = 0; nIdx < nLen; nIdx++)
	{
		nMod3 = nIdx % 3;
		if (nIdx > 0 && (nIdx * 4 / 3) % 76 === 0)
			sB64Enc += "\r\n";
		nUint24 |= aBytes[nIdx] << (16 >>> nMod3 & 24);
		if (nMod3 === 2 || aBytes.length - nIdx === 1)
		{
			sB64Enc += String.fromCharCode(uint6ToB64(nUint24 >>> 18 & 63), uint6ToB64(nUint24 >>> 12 & 63), uint6ToB64(nUint24 >>> 6 & 63), uint6ToB64(nUint24 & 63));
			nUint24 = 0;
		}
	}

	return sB64Enc.replace(/A(?=A$|$)/g, "=");
}


//
// Unicode and arbitrary value safe conversion between strings and Uint8Arrays
//
Convert.Uint8Array_to_string = function(aBytes)
{
	var sView = "";

	for (var nPart, nLen = aBytes.length, nIdx = 0; nIdx < nLen; nIdx++)
	{
		nPart = aBytes[nIdx];
		sView += String.fromCharCode(
			nPart > 251 && nPart < 254 && nIdx + 5 < nLen ? /* six bytes */
			/* (nPart - 252 << 32) is not possible in ECMAScript! So...: */
			(nPart - 252) * 1073741824 + (aBytes[++nIdx] - 128 << 24) + (aBytes[++nIdx] - 128 << 18) + (aBytes[++nIdx] - 128 << 12) + (aBytes[++nIdx] - 128 << 6) + aBytes[++nIdx] - 128
			: nPart > 247 && nPart < 252 && nIdx + 4 < nLen ? /* five bytes */
			(nPart - 248 << 24) + (aBytes[++nIdx] - 128 << 18) + (aBytes[++nIdx] - 128 << 12) + (aBytes[++nIdx] - 128 << 6) + aBytes[++nIdx] - 128
			: nPart > 239 && nPart < 248 && nIdx + 3 < nLen ? /* four bytes */
			(nPart - 240 << 18) + (aBytes[++nIdx] - 128 << 12) + (aBytes[++nIdx] - 128 << 6) + aBytes[++nIdx] - 128
			: nPart > 223 && nPart < 240 && nIdx + 2 < nLen ? /* three bytes */
			(nPart - 224 << 12) + (aBytes[++nIdx] - 128 << 6) + aBytes[++nIdx] - 128
			: nPart > 191 && nPart < 224 && nIdx + 1 < nLen ? /* two bytes */
			(nPart - 192 << 6) + aBytes[++nIdx] - 128
			: /* nPart < 127 ? */ /* one byte */
			nPart
		);
	}

	return sView;
}
Convert.string_to_Uint8Array = function(sDOMStr)
{
	var aBytes, nChr, nStrLen = sDOMStr.length, nArrLen = 0;

	/* mapping... */

	for (var nMapIdx = 0; nMapIdx < nStrLen; nMapIdx++)
	{
		nChr = sDOMStr.charCodeAt(nMapIdx);
		nArrLen += nChr < 0x80 ? 1 : nChr < 0x800 ? 2 : nChr < 0x10000 ? 3 : nChr < 0x200000 ? 4 : nChr < 0x4000000 ? 5 : 6;
	}

	aBytes = new Uint8Array(nArrLen);

	/* transcription... */

	for (var nIdx = 0, nChrIdx = 0; nIdx < nArrLen; nChrIdx++)
	{
		nChr = sDOMStr.charCodeAt(nChrIdx);
		if (nChr < 128)
		{
			/* one byte */
			aBytes[nIdx++] = nChr;
		}
		else if (nChr < 0x800)
		{
			/* two bytes */
			aBytes[nIdx++] = 192 + (nChr >>> 6);
			aBytes[nIdx++] = 128 + (nChr & 63);
		}
		else if (nChr < 0x10000)
		{
			/* three bytes */
			aBytes[nIdx++] = 224 + (nChr >>> 12);
			aBytes[nIdx++] = 128 + (nChr >>> 6 & 63);
			aBytes[nIdx++] = 128 + (nChr & 63);
		}
		else if (nChr < 0x200000)
		{
			/* four bytes */
			aBytes[nIdx++] = 240 + (nChr >>> 18);
			aBytes[nIdx++] = 128 + (nChr >>> 12 & 63);
			aBytes[nIdx++] = 128 + (nChr >>> 6 & 63);
			aBytes[nIdx++] = 128 + (nChr & 63);
		}
		else if (nChr < 0x4000000)
		{
			/* five bytes */
			aBytes[nIdx++] = 248 + (nChr >>> 24);
			aBytes[nIdx++] = 128 + (nChr >>> 18 & 63);
			aBytes[nIdx++] = 128 + (nChr >>> 12 & 63);
			aBytes[nIdx++] = 128 + (nChr >>> 6 & 63);
			aBytes[nIdx++] = 128 + (nChr & 63);
		}
		else /* if (nChr <= 0x7fffffff) */
		{
			/* six bytes */
			aBytes[nIdx++] = 252 + /* (nChr >>> 32) is not possible in ECMAScript! So...: */ (nChr / 1073741824);
			aBytes[nIdx++] = 128 + (nChr >>> 24 & 63);
			aBytes[nIdx++] = 128 + (nChr >>> 18 & 63);
			aBytes[nIdx++] = 128 + (nChr >>> 12 & 63);
			aBytes[nIdx++] = 128 + (nChr >>> 6 & 63);
			aBytes[nIdx++] = 128 + (nChr & 63);
		}
	}

	return aBytes;
}


//
// Converts all characters in a string that have equivalent entities to their ampersand/entity names.
// Based on https://gist.github.com/jonathantneal/6093551
//
Convert.string_to_html_entities = (function()
{
	'use strict';

	var data = '34quot38amp39apos60lt62gt160nbsp161iexcl162cent163pound164curren165yen166brvbar167sect168uml169copy170ordf171laquo172not173shy174reg175macr176deg177plusmn178sup2179sup3180acute181micro182para183middot184cedil185sup1186ordm187raquo188frac14189frac12190frac34191iquest192Agrave193Aacute194Acirc195Atilde196Auml197Aring198AElig199Ccedil200Egrave201Eacute202Ecirc203Euml204Igrave205Iacute206Icirc207Iuml208ETH209Ntilde210Ograve211Oacute212Ocirc213Otilde214Ouml215times216Oslash217Ugrave218Uacute219Ucirc220Uuml221Yacute222THORN223szlig224agrave225aacute226acirc227atilde228auml229aring230aelig231ccedil232egrave233eacute234ecirc235euml236igrave237iacute238icirc239iuml240eth241ntilde242ograve243oacute244ocirc245otilde246ouml247divide248oslash249ugrave250uacute251ucirc252uuml253yacute254thorn255yuml402fnof913Alpha914Beta915Gamma916Delta917Epsilon918Zeta919Eta920Theta921Iota922Kappa923Lambda924Mu925Nu926Xi927Omicron928Pi929Rho931Sigma932Tau933Upsilon934Phi935Chi936Psi937Omega945alpha946beta947gamma948delta949epsilon950zeta951eta952theta953iota954kappa955lambda956mu957nu958xi959omicron960pi961rho962sigmaf963sigma964tau965upsilon966phi967chi968psi969omega977thetasym978upsih982piv8226bull8230hellip8242prime8243Prime8254oline8260frasl8472weierp8465image8476real8482trade8501alefsym8592larr8593uarr8594rarr8595darr8596harr8629crarr8656lArr8657uArr8658rArr8659dArr8660hArr8704forall8706part8707exist8709empty8711nabla8712isin8713notin8715ni8719prod8721sum8722minus8727lowast8730radic8733prop8734infin8736ang8743and8744or8745cap8746cup8747int8756there48764sim8773cong8776asymp8800ne8801equiv8804le8805ge8834sub8835sup8836nsub8838sube8839supe8853oplus8855otimes8869perp8901sdot8968lceil8969rceil8970lfloor8971rfloor9001lang9002rang9674loz9824spades9827clubs9829hearts9830diams338OElig339oelig352Scaron353scaron376Yuml710circ732tilde8194ensp8195emsp8201thinsp8204zwnj8205zwj8206lrm8207rlm8211ndash8212mdash8216lsquo8217rsquo8218sbquo8220ldquo8221rdquo8222bdquo8224dagger8225Dagger8240permil8249lsaquo8250rsaquo8364euro';
	var charCodes = data.split(/[A-z]+/);
	var entities = data.split(/\d+/).slice(1);

	return function encodeHTMLEntities(text)
	{
		return text.replace(/[\u00A0-\u2666<>"'&]/g, function (match)
		{
			var charCode = String(match.charCodeAt(0));
			var index = charCodes.indexOf(charCode);
			return '&' + (entities[index] ? entities[index] : '#' + charCode) + ';';
		});
	};
})();
