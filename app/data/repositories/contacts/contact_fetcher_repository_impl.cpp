#include "contact_fetcher_repository_impl.h"

ContactFetcherRepositoryImpl::ContactFetcherRepositoryImpl()
{}

void ContactFetcherRepositoryImpl::sendContactListRequest()
{
    module->sendRequest();
}
