use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, Data, DeriveInput, Fields};

#[proc_macro_derive(AutoLog)]
pub fn derive_auto_log(input: TokenStream) -> TokenStream {
    let input = parse_macro_input!(input as DeriveInput);
    let struct_name = input.ident;

    let generate_fields = if let Data::Struct(data) = input.data {
        if let Fields::Named(fields) = data.fields {
            fields.named.into_iter().map(|f| {
                let field_name = f.ident.unwrap();
                let field_name_str = field_name.to_string();

                quote! {
                    self.#field_name.append_to(
                        logger,
                        &format!("{}/{}", path, #field_name_str)
                    );
                }
            })
        } else {
            panic!("AutoLog only supports structs with named fields");
        }
    } else {
        panic!("AutoLog only supports structs");
    };

    let expanded = quote! {
        impl AutoLog for #struct_name {
            fn append_to(&self, logger: &mut robot_rust::logging::Logger, path: &str) {
                #(#generate_fields)*
            }
        }
    };

    TokenStream::from(expanded)
}
