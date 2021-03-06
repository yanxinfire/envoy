#pragma once

#include "envoy/extensions/internal_redirect/allow_listed_routes/v3/allow_listed_routes_config.pb.h"
#include "envoy/extensions/internal_redirect/allow_listed_routes/v3/allow_listed_routes_config.pb.validate.h"
#include "envoy/router/internal_redirect.h"

#include "common/protobuf/message_validator_impl.h"
#include "common/protobuf/utility.h"

#include "extensions/internal_redirect/allow_listed_routes/allow_listed_routes.h"
#include "extensions/internal_redirect/well_known_names.h"

namespace Envoy {
namespace Extensions {
namespace InternalRedirect {

class AllowListedRoutesPredicateFactory : public Router::InternalRedirectPredicateFactory {
public:
  Router::InternalRedirectPredicateSharedPtr
  createInternalRedirectPredicate(const Protobuf::Message& config, absl::string_view) override {
    auto allow_listed_routes_config =
        MessageUtil::downcastAndValidate<const envoy::extensions::internal_redirect::
                                             allow_listed_routes::v3::AllowListedRoutesConfig&>(
            config, ProtobufMessage::getStrictValidationVisitor());
    return std::make_shared<AllowListedRoutesPredicate>(allow_listed_routes_config);
  }

  std::string name() const override {
    return InternalRedirectPredicateValues::get().AllowListedRoutesPredicate;
  }

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return std::make_unique<
        envoy::extensions::internal_redirect::allow_listed_routes::v3::AllowListedRoutesConfig>();
  }
};

} // namespace InternalRedirect
} // namespace Extensions
} // namespace Envoy
