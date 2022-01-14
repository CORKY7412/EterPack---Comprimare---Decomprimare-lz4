bool CLZObject::Compress()
{
	UINT iOutLen;
	BYTE * pbBuffer;

	pbBuffer = m_pbBuffer + sizeof(THeader);
	*(DWORD *) pbBuffer = ms_dwFourCC;
	pbBuffer += sizeof(DWORD);

	int destBufferSize = LZ4_compressBound(m_pHeader->dwRealSize);
	iOutLen = LZ4_compress_default((const char*)m_pbIn, (char*)pbBuffer, m_pHeader->dwRealSize, destBufferSize);
	if (iOutLen < 1) {
		TraceError("LZ4: LZ4_compress_default failed");
		return false;
	}

	m_pHeader->dwCompressedSize = iOutLen;
	m_bCompressed = true;
	return true;
}

bool CLZObject::Decompress(DWORD* pdwKey) {
	UINT uiSize;

	if (m_pHeader->dwEncryptSize) {
		DecryptBuffer buf(m_pHeader->dwEncryptSize);

		BYTE* pbDecryptedBuffer = (BYTE*)buf.GetBufferPtr();

		__Decrypt(pdwKey, pbDecryptedBuffer);

		if (*(DWORD*)pbDecryptedBuffer != ms_dwFourCC)
		{
			TraceError("LZObject: key incorrect");
			return false;
		}

		uiSize = LZ4_decompress_safe((const char*)pbDecryptedBuffer + sizeof(DWORD), (char*)m_pbBuffer, m_pHeader->dwCompressedSize, m_pHeader->dwRealSize);
	} else {
		uiSize = m_pHeader->dwRealSize;
		uiSize = LZ4_decompress_safe((const char*)m_pbIn, (char*)m_pbBuffer, m_pHeader->dwCompressedSize, m_pHeader->dwRealSize);
	}

	if (uiSize != m_pHeader->dwRealSize) {
		TraceError("LZObject: Size differs");
		return false;
	}

	return true;
}