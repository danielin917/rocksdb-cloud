
// Copyright (c) 2016-present, Rockset, Inc. All rights reserved.

#ifndef ROCKSDB_LITE
#include <iostream>
#include "cloud/azure/azure_env.h"
#include "cloud/cloud_storage_provider_impl.h"
#include "rocksdb/cloud/cloud_storage_provider.h"
#include "logging/logging.h"

#ifdef USE_AZURE

namespace ROCKSDB_NAMESPACE {

Status AzureEnv::NewAzureEnv(Env *env, const CloudEnvOptions& env_options,
                            const std::shared_ptr<Logger>& info_log,
                            CloudEnv** cenv) {
  return Status::OK();
}

Status AzureEnv::NewAzureEnv(Env *env, std::unique_ptr<CloudEnv>* cenv) {
  return Status::OK();
}

AzureEnv::AzureEnv(Env* _underlying_env, const CloudEnvOptions& _cloud_options) :
  CloudEnvImpl(_cloud_options, _underlying_env) {
  Log(InfoLogLevel::ERROR_LEVEL, GetLogger(), "Building azure env");
}

Status AzureEnv::PrepareOptions(const ConfigOptions& options) {
  if (cloud_env_options.storage_provider == nullptr) {
    Status s = CloudStorageProvider::CreateFromString(
      options, CloudStorageProviderImpl::kAzure(), &cloud_env_options.storage_provider);

    if (!s.ok()) {
    }
  }
  return CloudEnvImpl::PrepareOptions(options);
}

} // namespace

#endif // USE_AZURE
#endif // ROCKSDB_LITE
