#include <cppweb/Application.h>
#include <cppweb/Request.h>
#include <cppweb/Response.h>
#include <json/json.h> // For JSON parsing

#include "BooleanEvaluator.h"

class BooleanEvaluatorApp : public cppweb::Application {
public:
    void handleRequest(cppweb::Request& request, cppweb::Response& response) override {
        if (request.method() == cppweb::HttpMethod::POST && request.path() == "/evaluate") {
            // Parse the JSON body of the request
            Json::Value jsonData;
            Json::Reader reader;
            if (!reader.parse(request.body(), jsonData)) {
                response.setStatus(cppweb::HttpStatusCode::BadRequest);
                response.setBody("Error parsing JSON body");
                return;
            }

            // Check if the JSON contains the 'expression' field
            if (!jsonData.isMember("expression") || !jsonData["expression"].isString()) {
                response.setStatus(cppweb::HttpStatusCode::BadRequest);
                response.setBody("Missing or invalid 'expression' field in JSON");
                return;
            }

            // Get the expression from the JSON
            std::string expression = jsonData["expression"].asString();

            // Evaluate the expression
            bool result = evaluateBooleanExpression(expression);

            // Send the result back as JSON
            Json::Value jsonResponse;
            jsonResponse["result"] = result ? "True" : "False";

            response.setContentType("application/json");
            response.setBody(jsonResponse.toStyledString());
        } else {
            response.setStatus(cppweb::HttpStatusCode::NotFound);
            response.setBody("Not Found");
        }
    }
};

int main() {
    BooleanEvaluatorApp app;
    app.listen(8080); // Listen on port 8080
    return 0;
}
