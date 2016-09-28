/*
 * Copyright © 2012-2016 VMware, Inc.  All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the “License”); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an “AS IS” BASIS, without
 * warranties or conditions of any kind, EITHER EXPRESS OR IMPLIED.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

// This File impliments a class that creats a PKCS#10 Certiifcate Request.
// PKCS#10 is speced here, http://tools.ietf.org/html/rfc2986

// For the uninitiated :
//
// PKCS#10 is the Format of messages sent to a certification
// authority to request certification of a public key.

// From Wikipedia :

// A certificate signing request (also CSR or certification request) is a message
// sent from an applicant to a certificate authority in order to apply for a
// digital identity certificate. The most common format for CSRs is the PKCS#10
// specification and another is the Signed Public Key and Challenge Spkac
// format generated by some web browsers.

// Typical information required in a CSR

// Distinguished Name (DN) : This is fully qualified domain name that you wish to
// secure e.g. ‘www.mydomain.com’ or 'mail.mydomain.com'. This includes the Common Name
// (CN) e.g. 'www' or 'mail'

// Business name / Organisation : Usually the legal incorporated name of a company
// and should include any suffixes such as Ltd., Inc., or Corp.

// Department Name / Organisational Unit : HR, Finance, IT
// Town/City :      London, Paris, New York

// Province, Region, County or State : This should not be abbreviated
// e.g. Sussex, Normandy, New Jersey

// Country : The two-letter ISO code for the country where your organization is located
// e.g. GB, FR or US etc..

// An email address: An email address to contact the organisation.
// Usually the email address of the certificate administrator or IT department

// This file provides a set of functions that allow the users to create PKCS#10
// certificate request.

#include "includes.h"
#include "pkcs_csr.h"

// DWORD
// VMCAAllocatePKCS10Data(
//     PVMCA_PKCS_10_REQ_DATA* pCertRequestData
// )
// // This function allocates a VMCA specific structure
// // which carries the payload for creating a certificate
// // request. This function allocates and returns a zero
// // structure. Please see the definition of VMCA_PKCS_10_REQ_DATA
// // for more details
// //
// // Arguments :
// //         Pointer-Pointer to the Structure to be Allocated
// // Returns :
// //     Error code
// {
//     VMCAAllocateMemory(sizeof(VMCA_PKCS_10_REQ_DATA), (PVOID*) pCertRequestData);
//     bzero((PVOID) *pCertRequestData, sizeof(VMCA_PKCS_10_REQ_DATA));
//     return 0;
// }


DWORD
VMCACreateCACertificateFromRootCA(
    char* pszCAServerName,
    char* pszPrivateKeyFile,
    char* pszPassPhrase,
    PVMCA_PKCS_10_REQ_DATA pCertRequestData,
    int bCreateSelfSignedRootCA,
    char** ppszPemEncodedCertificate
)
// This function creates a private-public key pair that can used
// to sign another ceritificate, Please Note : This version
// of the API creats self-signed CA Certificates. 
//
// It is more secure to chain your certificate from some known
// trusted Enterprise CA.
//
// Arguments :
//          pszCAServerName : The Remote CA Server Name
//
//          pszPrivateKeyFile : The Private Key used for this CSR
//
//          pszPassPhrase : The Password for the Private Key File
//
//          pCertRequestData : The Data in the Certificate
//
//          bCreateSelfSignedRootCA : if this flag is set to TRUE,
//          and pszCAServerName == NULL, then we will create a 
//          self-signed ROOT CA Certificate.
//
//          pszPemEncodedCertificate : This pointer returns a pointer to the
//          certificate in PEM encoded format.
//
// Returns :
//      Error Code
{
    DWORD dwError = 0;
    if ( ( pszCAServerName == NULL ) && ( bCreateSelfSignedRootCA  ) )  {

    dwError = VMCASelfSignedCertificatePrivate( pCertRequestData, 
                                        pszPrivateKeyFile,
                                        pszPassPhrase,
                                        bCreateSelfSignedRootCA,
                                        ppszPemEncodedCertificate);

    BAIL_ON_ERROR(dwError);
        
    } else {

        // TODO :
        // 1) Generate a CSR and Call into Remote Server.
    } 

error :
    return dwError;
}

/**** TO REMOVE ***********************

DWORD
VMCACreateKeys(
    char* pszPath,
    char* pszFileName,
    char* pszPassPhrase,
    size_t uiKeyLength
)
// This function creates private-public key pair and writes it down in the
// specified path, The function creates FileName.pub.pem and FileName.priv.pem
// in the specified directory. The user should delete the files if they are not
// needed in the future.
//
// Arguments :
//          pszPath         : The Dirctory where the files will live
//          pszFileName     : The Prefix part of the files, 2 files pszFileName.priv.pem and pszFileName.pub.pem
//                              will be created in the directory pointed by pszPath
//          pszPassPhrase   : Optional Pass Word to protect the Key
//          uiKeyLength     : Key Length - Valid values are between 1024 and 16384
// Returns :
//      Error Code
//
// Notes : This function makes some assumptions on the users
// behalf. One of them is that assumption on bit size. If the
// user does not specify a Bit Size, then the this function will
// allocate a Key with 1024 Bits and use it. This is based on RSA's
// recommendation http://www.rsa.com/rsalabs/node.asp?id=2218 on
// Corporate Key lengths.
{
    DWORD dwError = 0;

    if ( ( pszPath == NULL ) ||
       ( pszFileName == NULL ) ) {
        dwError = ERROR_INVALID_PARAMETER;
        BAIL_ON_ERROR(dwError);
    }

    if ( (uiKeyLength < 1024) || (uiKeyLength > 16384) ) {
        dwError = ERROR_INVALID_PARAMETER;
        BAIL_ON_ERROR(dwError);
    }

    dwError = VMCAAllocatePrivateKeyP(pszPath,pszFileName,
                                      pszPassPhrase,uiKeyLength);

error :
    return dwError;
}
*/

// DWORD
// VMCACreateSigningRequest(
//     PVMCA_PKCS_10_REQ_DATA pCertRequestData,
//     char* pszPrivateKeyFile,
//     char* pszPassPhrase,
//     PVMCA_CSR* pAllocatedCSR
// )
// // This function creates a Signing Request which can be send to a Certificate authority
// // for its signature. This function creates something known as PKCS#10 , or a CSR
// // (Certificate Signing Reqeuest).
// //
// // Arguments :
// //  pCertRequestData - A ceritificate can have various data fields that your might choose to
// //  provide, this blob points to data that user wants to put in the certificate.
// //
// //  pszPrivateKeyFile - A File Path to the Private Certificate that is used for creating
// //  the CSR.
// //
// //  pszPassPhrase - Optional  Pass Phrase needed to open the Private key. If the key was protected
// //  using a Pass Phrase then that is the Pass Phrase needed here.
// //
// //  pAllocatedCSR - A pointer to a buffer where the  Actual allocated CSR will be written to.
// //
// // Returns :
// //  Error Code
// {
//     struct stat buffer;
//     DWORD dwError = 0;

//     if ( pCertRequestData == NULL) {
//         dwError = ERROR_INVALID_PARAMETER;
//         BAIL_ON_ERROR(dwError);
//     }

//     if (pszPrivateKeyFile == NULL) {
//         dwError = ERROR_INVALID_PARAMETER;
//         BAIL_ON_ERROR(dwError);
//     }

//     //
//     // Windows Porting Notes : use _stat defined in crt.dll
//     //
//     dwError = stat(pszPrivateKeyFile, &buffer);
//     BAIL_ON_ERROR(dwError);

//     dwError = VMCACreateSigningRequestP(pCertRequestData, pszPrivateKeyFile,
//                                         pszPassPhrase, pAllocatedCSR);

// error :
//     return dwError;
// }


// DWORD
// VMCACSR2PKCS10(
//     PVMCA_CSR pCSR,
//     PVMCA_PKCS_10_REQ_DATA pCertRequestData
// )
// {
//     return 0;
// }



// VOID
// VMCAFreePKCS10(
//     PVMCA_PKCS_10_REQ_DATA pCertRequestData
// )
// // This function takes an allocated PVMCA_PKCS_10_REQ_DATA structure
// // and deep frees it. Make sure that there are no dangling pointers.
// //
// // Arguments :
// //     pCertRequestData : The Request Data Structure pointer
// // Returns:
// //     None
// {
//     VMCASetPKCSMember(&pCertRequestData->pszName,       NULL);
//     VMCASetPKCSMember(&pCertRequestData->pszOU,         NULL);
//     VMCASetPKCSMember(&pCertRequestData->pszState,      NULL);
//     VMCASetPKCSMember(&pCertRequestData->pszEmail,      NULL);
//     VMCASetPKCSMember(&pCertRequestData->pszIPAddress,  NULL);
//     VMCAFreeMemory(pCertRequestData);
//     pCertRequestData = NULL;
// }



// VOID
// VMCASetPKCSMember(
//     LPSTR *ppszMember,
//     LPCSTR pszNewValue
// )
// // This function Sets the member value of a PKCS_10_REQ,
// // if member is pointing to something valid, then it is freed,
// // before allocating and copying new structure
// //g
// // Args :
// //  ppszMemeber - Pointer Pointer to the Memeber variable
// //  pszNewValue - Pointer to the NewValue to be set, setting NULL
// //  frees the old object and initializes the pointer to NULL.
// //
// // Returns :
// //  None
// {
//     VMCA_SAFE_FREE_STRINGA(*ppszMember);
 
//     if (pszNewValue != NULL) {
//         VMCAAllocateStringA(pszNewValue,ppszMember);   
//     }
// }

// DWORD
// VMCAInitPKCS10DataUnicode(
//     PCWSTR pwszSubject,
//     PCWSTR pwszName,
//     PCWSTR pwszOU,
//     PCWSTR pwszState,
//     PCWSTR pwszCountry,
//     PCWSTR pwszEmail,
//     PCWSTR pwszIPAddress,
//     DWORD ttl,
//     PVMCA_PKCS_10_REQ_DATA pCertRequestData
// )
// // This function initilizes the pCertRequstData with appropriate
// // values for the certificate. Most of these values are Optional
// // other than Subject and Country. We need that in the Certificate
// // for it to be a vaild certificate.
// //
// // Arguments :
// //     The Names of the Arguments indicate what it is, Please
// //     look up a certificate defintion to understand what they
// //     mean.
// //
// //     Country is a 2 CHAR country code, like US, IN etc.
// //     if it is anything other than 2 CHARs this function will
// //     fail.
// //
// // Returns :
// //     Error Code

// {
//     LPSTR pszName = NULL;
//     LPSTR pszOU = NULL;
//     LPSTR pszState = NULL;
//     LPSTR pszEmail = NULL;
//     LPSTR pszIPAddress = NULL;
//     LPSTR pszCountry = NULL;

//     DWORD dwError = 0;
 
//     if (pCertRequestData == NULL) {
//         dwError = ERROR_INVALID_PARAMETER;
//         BAIL_ON_ERROR(dwError);
//     }

 
//     // Check if the country is a 2 CHAR CODE
//     dwError = ConvertUnicodetoAnsiString(pwszCountry,&pszCountry);
//     BAIL_ON_ERROR(dwError);

//     if (strlen(pszCountry) !=  sizeof(pCertRequestData->pszCountry)) {
//         dwError = ERROR_INVALID_PARAMETER;
//         BAIL_ON_ERROR(dwError);
//     }

//     dwError = ConvertUnicodetoAnsiString(pwszName, &pszName);
//     BAIL_ON_ERROR(dwError);

//     dwError = ConvertUnicodetoAnsiString(pwszOU, &pszOU);
//     BAIL_ON_ERROR(dwError);

//     dwError = ConvertUnicodetoAnsiString(pwszState, &pszState);
//     BAIL_ON_ERROR(dwError);

//     dwError = ConvertUnicodetoAnsiString(pwszEmail, &pszEmail);
//     BAIL_ON_ERROR(dwError);

//     dwError = ConvertUnicodetoAnsiString(pwszIPAddress, &pszIPAddress);
//     BAIL_ON_ERROR(dwError);



//     VMCASetPKCSMember(&pCertRequestData->pszName, pszName);
//     VMCASetPKCSMember(&pCertRequestData->pszOU, pszOU);
//     VMCASetPKCSMember(&pCertRequestData->pszState, pszState);
//     VMCASetPKCSMember(&pCertRequestData->pszEmail, pszEmail);
//     VMCASetPKCSMember(&pCertRequestData->pszIPAddress, pszIPAddress);

//     bzero(pCertRequestData->pszCountry, sizeof(pCertRequestData->pszCountry));

//     pCertRequestData->pszCountry[0] = pszCountry[0];
//     pCertRequestData->pszCountry[1] = pszCountry[1];
//     pCertRequestData->uiExpirationTimeInSeconds = ttl;
   
// error:
//     VMCA_SAFE_FREE_STRINGA(pszCountry);
//     VMCA_SAFE_FREE_STRINGA(pszName);
//     VMCA_SAFE_FREE_STRINGA(pszOU);
//     VMCA_SAFE_FREE_STRINGA(pszState);
//     VMCA_SAFE_FREE_STRINGA(pszEmail);
//     VMCA_SAFE_FREE_STRINGA(pszIPAddress);

//     return dwError;
// }
